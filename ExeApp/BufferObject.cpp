#include "BufferObject.h"

void UniformBufferObject::bufferUpdateFunction(dzg* app, void* bufferMapped)
{
		UniformBufferObject ubo{};
		ubo.model = glm::mat4(1.0f);
		ubo.view = app->camera->ViewMatrix;
		ubo.proj = app->camera->ProjectionMatrix;
		//	glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f)); //app->camera->ViewMatrix; //TODO - remove hardcoding
		//ubo.proj = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.0f, 1.0f);// app->camera->ProjectionMatrix;
	//	ubo.proj = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);// app->camera->ProjectionMatrix;
	//	ubo.proj[1][1] *= -1;
		memcpy(bufferMapped, &ubo, sizeof(ubo));
}

void ObjectDataBuffer::bufferUpdateFunction(dzg* app, void* bufferMapped)
{

	ObjectDataBuffer* objectArray = (ObjectDataBuffer*)bufferMapped;

	for (size_t i = 0; i < app->m_scene->MeshVec.size(); ++i)
	{
		objectArray[i].Model = app->m_scene->MeshVec[i].Model;
		objectArray[i].Color = app->m_scene->MeshVec[i].Color;
	}
}
