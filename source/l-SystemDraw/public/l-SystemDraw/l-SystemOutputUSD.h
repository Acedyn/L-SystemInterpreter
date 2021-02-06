#pragma once
#define NOMINMAX
#define TBB_USE_ASSERT 0

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usdGeom/mesh.h>
#include <pxr/usd/usdGeom/xform.h>
#include <pxr/usd/usdGeom/basisCurves.h>

#include <string>

namespace LSystem
{

	class OutputUSD
	{
	public:
		// Constructors / Destructors
		OutputUSD(std::string _root);
		~OutputUSD() { }

		pxr::UsdStageRefPtr getStage() const { return stage; }

		void setMesh(pxr::VtArray<pxr::GfVec3f> _vertices, pxr::VtArray<int> _faceVertexCount, pxr::VtArray<int> _faceIndices);

		void writeToDisk(std::string _location);

	private:
		pxr::UsdStageRefPtr stage;
		pxr::UsdGeomXform xform;
		pxr::UsdGeomBasisCurves curve;
		pxr::UsdGeomMesh mesh;

		std::string root;
	};
}