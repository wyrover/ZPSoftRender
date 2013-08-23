#ifndef ZP_MESHMANAGER
#define ZP_MESHMANAGER

#include "ZPDependency.h"
#include "Singleton.h"

namespace Render
{
	class IRender;
}

namespace Math
{
	class Matrix4;
}

namespace Resource
{
	class Mesh;
	class IMeshLoader;
	 
	class  MeshManager : public Util::SingletonT<MeshManager>
	{
	public:
		MeshManager(void);
		virtual ~MeshManager(void);

		Mesh* CreateOrRetrieveMesh( const String& name );
			 
		Mesh* RetrieveMesh( const String& name );
		 
	    bool DeleteMeshByName( const String& name );
		 
		bool DeleteMesh( Mesh* pMesh );

	    void DeleteAllMesh( void ); 

	    void DrawActiveMesh( Render::IRender* pRenderer, const Math::Matrix4& localToWorldMat);

	    void SetFirstMeshActive( void );

	    void SetNextMeshActive( void );

	protected:

		typedef std::map<String,Mesh*> meshTable_t;

		meshTable_t m_meshes;						///>模型列表
		meshTable_t::iterator m_itActiveMesh;  ///>当前所显示的模型迭代器
		IMeshLoader* m_pLoader;					///>模型读取器

	}; 

}//namespace Resource

#endif//ZP_MESHMANAGER