// Modelo3D.cpp
#include "Modelo3D.h"

Modelo3D::Modelo3D(float x, float y, float z,
                   float escalaX, float escalaY, float escalaZ,
                   float rotX, float rotY, float rotZ)
    : posicao(x, y, z),
      escala(escalaX, escalaY, escalaZ),
      rotacao(rotX, rotY, rotZ)
{
  idTextura = 0;
}

void Modelo3D::carregarModelo(const char *caminhoModelo)
{
  std::ifstream arquivo(caminhoModelo);
  if (!arquivo.is_open())
  {
    std::cerr << "Erro ao abrir o arquivo: " << caminhoModelo << std::endl;
    return;
  }

  // Vetores temporários para armazenar todos os dados do arquivo
  std::vector<Ponto> temp_vertices;
  std::vector<Ponto> temp_normais;
  std::vector<std::pair<float, float>> temp_texturas;

  // Limpar vetores existentes
  vertices.clear();
  normais.clear();
  coordTextura.clear();

  std::string linha;
  while (std::getline(arquivo, linha))
  {
    std::istringstream iss(linha);
    std::string tipo;
    iss >> tipo;

    if (tipo == "v")
    { // Vértice
      float x, y, z;
      iss >> x >> y >> z;
      temp_vertices.push_back(Ponto(x, y, z));
    }
    else if (tipo == "vn")
    { // Normal
      float x, y, z;
      iss >> x >> y >> z;
      temp_normais.push_back(Ponto(x, y, z));
    }
    else if (tipo == "vt")
    { // Coordenada de textura
      float u, v;
      iss >> u >> v;
      temp_texturas.push_back(std::make_pair(u, v));
    }
    else if (tipo == "f")
    { // Face
      std::string vertex1, vertex2, vertex3;
      iss >> vertex1 >> vertex2 >> vertex3;

      // Função auxiliar para processar cada vértice da face
      auto processVertex = [&](const std::string &vertex)
      {
        std::istringstream viss(vertex);
        std::string index_str;
        std::vector<int> indices;

        // Separar os índices (formato v/vt/vn ou v//vn ou v)
        while (std::getline(viss, index_str, '/'))
        {
          if (index_str.empty())
          {
            indices.push_back(0); // Índice 0 para dados ausentes
          }
          else
          {
            indices.push_back(std::stoi(index_str));
          }
        }

        // Ajustar índices (OBJ usa indexação baseada em 1)
        int v_idx = indices[0] - 1;
        int vt_idx = indices.size() > 1 ? indices[1] - 1 : -1;
        int vn_idx = indices.size() > 2 ? indices[2] - 1 : -1;

        // Adicionar dados aos vetores finais
        if (v_idx >= 0 && v_idx < temp_vertices.size())
        {
          vertices.push_back(temp_vertices[v_idx]);
        }

        if (vt_idx >= 0 && vt_idx < temp_texturas.size())
        {
          coordTextura.push_back(temp_texturas[vt_idx]);
        }
        else if (!temp_texturas.empty())
        {
          coordTextura.push_back(std::make_pair(0.0f, 0.0f));
        }

        if (vn_idx >= 0 && vn_idx < temp_normais.size())
        {
          normais.push_back(temp_normais[vn_idx]);
        }
        else if (!temp_normais.empty())
        {
          // Se não houver normal específica mas existirem normais no arquivo,
          // adiciona uma normal padrão
          normais.push_back(Ponto(0.0f, 1.0f, 0.0f));
        }
      };

      // Processar cada vértice da face
      processVertex(vertex1);
      processVertex(vertex2);
      processVertex(vertex3);
    }
  }

  arquivo.close();

  // Se não houver normais, gerar normais simples
  if (normais.empty() && !vertices.empty())
  {
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
      if (i + 2 < vertices.size())
      {
        Ponto v1 = vertices[i];
        Ponto v2 = vertices[i + 1];
        Ponto v3 = vertices[i + 2];

        // Calcular vetores das arestas
        Ponto edge1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
        Ponto edge2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);

        // Calcular produto vetorial para obter a normal
        Ponto normal(
            edge1.y * edge2.z - edge1.z * edge2.y,
            edge1.z * edge2.x - edge1.x * edge2.z,
            edge1.x * edge2.y - edge1.y * edge2.x);

        // Normalizar
        float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        if (length > 0)
        {
          normal.x /= length;
          normal.y /= length;
          normal.z /= length;
        }

        // Adicionar a mesma normal para os três vértices do triângulo
        normais.push_back(normal);
        normais.push_back(normal);
        normais.push_back(normal);
      }
    }
  }

  std::cout << "Modelo carregado com sucesso: " << vertices.size() << " vertices, "
            << normais.size() << " normais, "
            << coordTextura.size() << " coords de textura." << std::endl;
}

void Modelo3D::carregarTextura(const char *caminhoTextura)
{
  idTextura = LoadTexture(caminhoTextura);
  if (idTextura == (GLuint)-1)
  {
    std::cerr << "Erro ao carregar a textura do modelo: " << caminhoTextura << std::endl;
    exit(1);
  }
}

void Modelo3D::desenhar()
{
  glPushMatrix();

  // Aplica transformações na ordem: translação, rotação, escala
  glTranslatef(posicao.x, posicao.y, posicao.z);

  glRotatef(rotacao.x, 1.0f, 0.0f, 0.0f);
  glRotatef(rotacao.y, 0.0f, 1.0f, 0.0f);
  glRotatef(rotacao.z, 0.0f, 0.0f, 1.0f);

  glScalef(escala.x, escala.y, escala.z);

  // Ativa a textura se houver
  if (idTextura != 0)
  {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, idTextura);
  }
  else
  {
    glColor3f(colorR, colorG, colorB);
  }

  // Aqui você implementaria o desenho do modelo
  // Este é um exemplo simplificado
  glBegin(GL_TRIANGLES);
  for (size_t i = 0; i < vertices.size(); i++)
  {
    if (!normais.empty())
    {
      glNormal3f(normais[i].x, normais[i].y, normais[i].z);
    }
    if (!coordTextura.empty())
    {
      glTexCoord2f(coordTextura[i].first, coordTextura[i].second);
    }
    glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
  }
  glEnd();

  if (idTextura != 0)
  {
    glDisable(GL_TEXTURE_2D);
  }

  glPopMatrix();
}

void Modelo3D::setPosicao(float x, float y, float z)
{
  posicao = Ponto(x, y, z);
}

void Modelo3D::setEscala(float x, float y, float z)
{
  escala = Ponto(x, y, z);
}

void Modelo3D::setRotacao(float x, float y, float z)
{
  rotacao = Ponto(x, y, z);
}

void Modelo3D::setColor(float r, float g, float b)
{
  colorR = r;
  colorG = g;
  colorB = b;
}