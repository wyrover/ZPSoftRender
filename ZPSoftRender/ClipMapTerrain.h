#ifndef ZP_CLIPMAPTERRAIN
#define ZP_CLIPMAPTERRAIN

#include "ClipMapTerrainDefine.h"
#include "IRender.h"
#include "Singleton.h"
#include "ClipMapTerrainRenderDataCache.h"

#define TERRAIN_MASK_SHOW_ALL  (\
											Terrain::SHOW_OUTER_TILES|Terrain::SHOW_CENTER_TILE|Terrain::SHOW_GAP_TILES|\
											Terrain::SHOW_LEFT_TOP_L_TILE|Terrain::SHOW_LEFT_BOTTOM_L_TILE|Terrain::SHOW_RIGHT_TOP_L_TILE|\
											Terrain::SHOW_RIGHT_BOTTOM_L_TILE|Terrain::SHOW_FIXED_UP_RING)  
#define TERRAIN_MASK_SHOW_OUTER_TILES		 Terrain::SHOW_OUTER_TILES
#define TERRAIN_MASK_SHOW_CENTER_TILE       Terrain::SHOW_CENTER_TILE
#define TERRAIN_MASK_SHOW_GAP_TILES			 Terrain::SHOW_GAP_TILES
#define TERRAIN_MASK_SHOW_L_FIXED_TILE       (Terrain::SHOW_LEFT_TOP_L_TILE|Terrain::SHOW_LEFT_BOTTOM_L_TILE|Terrain::SHOW_RIGHT_TOP_L_TILE|Terrain::SHOW_RIGHT_BOTTOM_L_TILE)
#define TERRAIN_MASK_SHOW_FIXED_RING		Terrain::SHOW_FIXED_UP_RING

namespace Terrain
{

	class ClipMapLevel; 
	 
	class ClipMapTerrain : public Util::SingletonT<ClipMapTerrain>
	{
	public:
		ClipMapTerrain(void);
		virtual ~ClipMapTerrain(void);

		/**
		* @brief 初始化剪切图地形
		* @param strMapName 剪切图文件路径
		* @param uiClipMapPow 剪切图的幂，初始化会根据幂值计算剪切图大小(整数)
		* @param v3TerrainOrigin 地形原点（左上角）
		* @param fGridWidth		地形格宽（最精细层的格宽度，以米为单位）
		*/
		void Init( LPDIRECT3DDEVICE9 pDevice , const String& strMapName , const unsigned int uiClipMapPow, const Math::Vec3& v3TerrainOrigin , const float fGridWidth ); 
		void Destroy( void );
		void Update(  const Math::Vec3 v3CamPos  );  
		void CameraCollision( const Math::Vec3& v3CamPos , Math::Vec3& v3FinalPos );
		void GetRenderOps( std::vector<Render::D3DRenderOperation*>& opList );
		void OnLostDevice( void );
		void OnResetDevice( void );
		void SetMask( unsigned int uiMask ){ m_uiShowMask = uiMask; }
		unsigned int GetMask( void ) const { return m_uiShowMask; }
	protected: 
		ClipMapGridPos _WorldPos2GridPos( const Math::Vec3& v3Pos );
	protected:
		LPDIRECT3DDEVICE9 m_pDevice;
		String m_strMapName;					//高度图名
		unsigned int m_uiClipMapSize;		//剪切图大小
		unsigned int m_uiClipMapPow;		//剪切图大小的幂
		Math::Vec3 m_v3CamPos;			//摄像机位置
		Math::Vec3 m_v3TerrainOrigin;     //地形原点
		float			   m_fGridWidth;			//格宽度 
		ClipMapGridPos m_CamPos;			//相机映射到地形采样点的坐标
		
		unsigned int	   m_uiLevelNum;		//层数量
		ClipMapLevel* m_pLevels;				//剪切图层

		unsigned int		m_uiShowMask;	//地形区块显示掩码

		std::vector<Render::D3DRenderOperation*> m_tmpOpList;
		ClipMapTerrainRenderDataCache m_renderDataCache;
	};

}//namespace Terrain

#endif