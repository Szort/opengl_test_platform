#pragma once

#include "AEObject.h"
#include "AEScene.h"
#include "AEFrameBuffer.h"

struct AEVertexArrayPackeg
{
	aiVector3D	position;
	aiColor4D	color;
	aiVector3D	normal;
	aiVector3D	texCoord;
};

struct AEDrawList
{
	// Packed data
	std::vector<AEVertexArrayPackeg>	vertex_data;
	std::vector<uint32_t>				indices_data;

	// Indirect draw command lists
	std::vector<AEDrawObjectsCommand>	CommandList;
	std::vector<AEObjectData>			ObjectList;
	std::vector<uint32_t>				IndexList;
};

struct AEImportDataSlice
{
	std::vector<AEVertexArrayPackeg>	vertex_data;
	std::vector<uint32_t>				indices_data;
};

struct AEGlobalParameters
{
	glm::mat4				CameraVPMatrix;		// 64-byte

	AEGlobalParameters() :
		CameraVPMatrix(glm::mat4(1.0f))
	{};
};

class AEEngine
{
	// Need to construct for static and dynamic objects
	uint32_t			VertexArrayObject;
	uint32_t			VertexBufferObject;
	uint32_t			IndicesBufferObject;
	uint32_t			DrawIndexObject;
	uint32_t			DrawCommandObject;
	void*				vertexArrayPtr;
	void*				indicesArrayPtr;
	void*				drawIndexesPtr;
	void*				drawCommandPtr;

	// All shader storage buffers need to be global
	uint32_t			ObjectDataSSBO;
	void*				objectDataPtr;

	// All uniform buffers need to be global
	uint32_t			GlobalParamsUBO;
	void*				globalParamsPtr;

	// picking object stuff
	uint32_t			PickedID;

public:
	static float				FpsCap;
	static double				RenderTime;
	static double				SleepTime;
	static bool					DebugBBox;
	static int					SelectedID;
	static AEGlobalParameters	GlobalUBO;

	AEDrawList					DrawList;

	AEEngine() {};
	~AEEngine() {};

	void SetPickedID(uint32_t id) { PickedID = id; };
	const uint32_t GetPickedID() { return PickedID; };

	void ConstructData(AEScene& scene);
	void CompileVAO();
	void CreateDrawCommandBuffer();
	void CreateVertexBuffer();
	void CreateUniformBuffer();
	void CreateShaderStorageBuffer();

	void CopyData_GPU();
	void UpdateUBO_GPU();

	void DrawGeometry();
	void DrawSelected();
	void DrawBoundingBox();
	void DrawQuad();
	void BindVAO();
	void UnbindVAO();
	void Idle();
}; 