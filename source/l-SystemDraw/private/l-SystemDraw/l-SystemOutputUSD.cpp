#include "l-SystemDraw/l-SystemOutputUSD.h"
#include "l-SystemDraw/l-SystemDrawBuffer.h"


LSystem::OutputUSD::OutputUSD(std::string _root) :
	stage(pxr::UsdStage::CreateInMemory()),
	root(_root),
	xform(pxr::UsdGeomXform::Define(stage, pxr::SdfPath("/" + _root)))
{
	stage->GetRootLayer()->SetDocumentation("Generated layer from LSystemInterpreter");
}


std::ostream& operator<<(std::ostream& stream, const LSystem::OutputUSD& _outputUSD)
{
	std::string _printStage;
	_outputUSD.getStage()->GetRootLayer()->ExportToString(&_printStage);
	stream << _printStage;

	return stream;
}


void LSystem::OutputUSD::setMesh(pxr::VtArray<pxr::GfVec3f> _vertices, pxr::VtArray<int> _faceVertexCount, pxr::VtArray<int> _faceIndices)
{
	mesh = pxr::UsdGeomMesh::Define(stage, pxr::SdfPath("/" + root + "/mesh"));

	mesh.CreatePointsAttr(pxr::VtValue{ _vertices });
	mesh.CreateFaceVertexCountsAttr(pxr::VtValue{ _faceVertexCount });
	mesh.CreateFaceVertexIndicesAttr(pxr::VtValue{ _faceIndices });
}


void LSystem::OutputUSD::writeToDisk(std::string _location)
{
	stage->GetRootLayer()->Export(_location);
}