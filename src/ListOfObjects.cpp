#include "ListOfObjects.h"

ListOfObjects::ListOfObjects() {}

ListOfObjects::~ListOfObjects()
{
  for (auto obj : objects)
  {
    delete obj;
  }
}

void ListOfObjects::addObject(const std::string &filePath, const Ponto &position, const Ponto &scale, const Ponto &rotation, float r, float g, float b)
{
  ObjectProperties props;
  props.filePath = filePath;
  props.position = position;
  props.scale = scale;
  props.rotation = rotation;
  props.color[0] = r;
  props.color[1] = g;
  props.color[2] = b;
  settings.push_back(props);
}

void ListOfObjects::initializeObjects()
{
  for (const auto &props : settings)
  {
    Modelo3D *model = new Modelo3D(props.position.x, props.position.y, props.position.z);

    model->setEscala(props.scale.x, props.scale.y, props.scale.z);
    model->setRotacao(props.rotation.x, props.rotation.y, props.rotation.z);
    model->setColor(props.color[0], props.color[1], props.color[2]);
    objects.push_back(model);
  }
}

void ListOfObjects::renderAll()
{
  for (auto obj : objects)
  {
    obj->desenhar();
  }
}
