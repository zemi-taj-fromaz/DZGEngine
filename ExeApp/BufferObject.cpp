#include "BufferObject.h"

void UniformBufferObject::bufferUpdateFunction(dzg* app, void* bufferMapped)
{
		UniformBufferObject ubo{};
		ubo.model = glm::mat4(1.0f);
		ubo.view = app->camera->ViewMatrix;
		ubo.proj = app->camera->ProjectionMatrix;
		memcpy(bufferMapped, &ubo, sizeof(ubo));
}

void ResolutionBufferObject::bufferUpdateFunction(dzg* app, void* bufferMapped)
{
	ResolutionBufferObject rbo{};
	rbo.width = app->GetWidth();
	rbo.height = app->GetHeight();
	memcpy(bufferMapped, &rbo, sizeof(rbo));
}

void ObjectDataBuffer::bufferUpdateFunction(dzg* app, void* bufferMapped)
{

	ObjectDataBuffer* objectArray = (ObjectDataBuffer*)bufferMapped;

	for (size_t i = 0; i < app->m_scene->MeshVec.size(); ++i)
	{
		objectArray[i].Model = app->m_scene->MeshVec[i]->Model;
		objectArray[i].Color = app->m_scene->MeshVec[i]->Color;
	}
}
