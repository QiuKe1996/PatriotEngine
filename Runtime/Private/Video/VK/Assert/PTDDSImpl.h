#include <stdint.h>

//DirectDraw Surface
//http://msdn.microsoft.com/en-us/library/windows/desktop/bb943982

#define DDS_MAGIC 0X20534444U

struct DDS_HEADER
{
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	struct DDS_PIXELFORMAT
	{
		uint32_t dwSize;
		uint32_t dwFlags;
		uint32_t dwFourCC;
		uint32_t dwRGBBitCount;
		uint32_t dwRBitMask;
		uint32_t dwGBitMask;
		uint32_t dwBBitMask;
		uint32_t dwABitMask;
	}ddspf;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
};

#define DDSD_DEPTH 0X00800000U
#define DDSD_MIPMAPCOUNT 0X00020000U
#define DDSD_CAPS 0X00000001U

#define DDSCAPS2_CUBEMAP 0X00000200U
#define DDSCAPS2_CUBEMAP_POSITIVEX 0X00000400U
#define DDSCAPS2_CUBEMAP_NEGATIVEX 0X00000800U
#define DDSCAPS2_CUBEMAP_POSITIVEY 0X00001000U
#define DDSCAPS2_CUBEMAP_NEGATIVEY 0X00002000U
#define DDSCAPS2_CUBEMAP_POSITIVEZ 0X00004000U
#define DDSCAPS2_CUBEMAP_NEGATIVEZ 0X00008000U

#define DDPF_FOURCC 0X00000004U
#define DDPF_RGB 0X00000040U
#define DDPF_YUV 0X00000200U
#define DDPF_LUMINANCE 0X00020000U
#define DDPF_ALPHA 0X00000002U
#define DDPF_ALPHAPIXELS 0X00000001U

#define FOURCC_DX10 0X30315844U
#define FOURCC_DXT1 0X31545844U
#define FOURCC_DXT3 0X33545844U
#define FOURCC_DXT5 0X35545844U
#define FOURCC_DXT2 0X32545844U
#define FOURCC_DXT4 0X34545844U

#define FOURCC_FMTR16F 111U
#define FOURCC_FMTG16R16F 112U
#define FOURCC_FMTA16B16G16R16F 113U
#define FOURCC_FMTR32F 114U
#define FOURCC_FMTG32R32F 115U
#define FOURCC_FMTA32B32G32R32F 116U

struct DDS_HEADER_DXT10
{
	uint32_t Format;
	uint32_t Dimension;
	uint32_t MiscFlags;
	uint32_t ArraySize;
	uint32_t MiscFlags2;
};

#define DXT10_FORMAT_UNKNOWN 0U
#define DXT10_FORMAT_R32G32B32A32_TYPELESS 1U
#define DXT10_FORMAT_R32G32B32A32_FLOAT 2U
#define DXT10_FORMAT_R32G32B32A32_UINT 3U
#define DXT10_FORMAT_R32G32B32A32_SINT 4U
#define DXT10_FORMAT_R32G32B32_TYPELESS 5U
#define DXT10_FORMAT_R32G32B32_FLOAT 6U
#define DXT10_FORMAT_R32G32B32_UINT 7U
#define DXT10_FORMAT_R32G32B32_SINT 8U
#define DXT10_FORMAT_R16G16B16A16_TYPELESS 9U
#define DXT10_FORMAT_R16G16B16A16_FLOAT 10U
#define DXT10_FORMAT_R16G16B16A16_UNORM 11U
#define DXT10_FORMAT_R16G16B16A16_UINT 12U
#define DXT10_FORMAT_R16G16B16A16_SNORM 13U
#define DXT10_FORMAT_R16G16B16A16_SINT 14U
#define DXT10_FORMAT_R32G32_TYPELESS 15U
#define DXT10_FORMAT_R32G32_FLOAT 16U
#define DXT10_FORMAT_R32G32_UINT 17U
#define DXT10_FORMAT_R32G32_SINT 18U
#define DXT10_FORMAT_R32G8X24_TYPELESS 19U
#define DXT10_FORMAT_D32_FLOAT_S8X24_UINT 20U
#define DXT10_FORMAT_R32_FLOAT_X8X24_TYPELESS 21U
#define DXT10_FORMAT_X32_TYPELESS_G8X24_UINT 22U
#define DXT10_FORMAT_R10G10B10A2_TYPELESS 23U
#define DXT10_FORMAT_R10G10B10A2_UNORM 24U
#define DXT10_FORMAT_R10G10B10A2_UINT 25U
#define DXT10_FORMAT_R11G11B10_FLOAT 26U
#define DXT10_FORMAT_R8G8B8A8_TYPELESS 27U
#define DXT10_FORMAT_R8G8B8A8_UNORM 28U
#define DXT10_FORMAT_R8G8B8A8_UNORM_SRGB 29U
#define DXT10_FORMAT_R8G8B8A8_UINT 30U
#define DXT10_FORMAT_R8G8B8A8_SNORM 31U
#define DXT10_FORMAT_R8G8B8A8_SINT 32U
#define DXT10_FORMAT_R16G16_TYPELESS 33U
#define DXT10_FORMAT_R16G16_FLOAT 34U
#define DXT10_FORMAT_R16G16_UNORM 35U
#define DXT10_FORMAT_R16G16_UINT 36U
#define DXT10_FORMAT_R16G16_SNORM 37U
#define DXT10_FORMAT_R16G16_SINT 38U
#define DXT10_FORMAT_R32_TYPELESS 39U
#define DXT10_FORMAT_D32_FLOAT 40U
#define DXT10_FORMAT_R32_FLOAT 41U
#define DXT10_FORMAT_R32_UINT 42U
#define DXT10_FORMAT_R32_SINT 43U
#define DXT10_FORMAT_R24G8_TYPELESS 44U
#define DXT10_FORMAT_D24_UNORM_S8_UINT 45U
#define DXT10_FORMAT_R24_UNORM_X8_TYPELESS 46U
#define DXT10_FORMAT_X24_TYPELESS_G8_UINT 47U
#define DXT10_FORMAT_R8G8_TYPELESS 48U
#define DXT10_FORMAT_R8G8_UNORM 49U
#define DXT10_FORMAT_R8G8_UINT 50U
#define DXT10_FORMAT_R8G8_SNORM 51U
#define DXT10_FORMAT_R8G8_SINT 52U
#define DXT10_FORMAT_R16_TYPELESS 53U
#define DXT10_FORMAT_R16_FLOAT 54U
#define DXT10_FORMAT_D16_UNORM 55U
#define DXT10_FORMAT_R16_UNORM 56U
#define DXT10_FORMAT_R16_UINT 57U
#define DXT10_FORMAT_R16_SNORM 58U
#define DXT10_FORMAT_R16_SINT 59U
#define DXT10_FORMAT_R8_TYPELESS 60U
#define DXT10_FORMAT_R8_UNORM 61U
#define DXT10_FORMAT_R8_UINT 62U
#define DXT10_FORMAT_R8_SNORM 63U
#define DXT10_FORMAT_R8_SINT 64U
#define DXT10_FORMAT_A8_UNORM 65U
#define DXT10_FORMAT_R1_UNORM 66U
#define DXT10_FORMAT_R9G9B9E5_SHAREDEXP 67U
#define DXT10_FORMAT_R8G8_B8G8_UNORM 68U
#define DXT10_FORMAT_G8R8_G8B8_UNORM 69U
#define DXT10_FORMAT_BC1_TYPELESS 70U
#define DXT10_FORMAT_BC1_UNORM 71U
#define DXT10_FORMAT_BC1_UNORM_SRGB 72U
#define DXT10_FORMAT_BC2_TYPELESS 73U
#define DXT10_FORMAT_BC2_UNORM 74U
#define DXT10_FORMAT_BC2_UNORM_SRGB 75U
#define DXT10_FORMAT_BC3_TYPELESS 76U
#define DXT10_FORMAT_BC3_UNORM 77U
#define DXT10_FORMAT_BC3_UNORM_SRGB 78U
#define DXT10_FORMAT_BC4_TYPELESS 79U
#define DXT10_FORMAT_BC4_UNORM 80U
#define DXT10_FORMAT_BC4_SNORM 81U
#define DXT10_FORMAT_BC5_TYPELESS 82U
#define DXT10_FORMAT_BC5_UNORM 83U
#define DXT10_FORMAT_BC5_SNORM 84U
#define DXT10_FORMAT_B5G6R5_UNORM 85U
#define DXT10_FORMAT_B5G5R5A1_UNORM 86U
#define DXT10_FORMAT_B8G8R8A8_UNORM 87U
#define DXT10_FORMAT_B8G8R8X8_UNORM 88U
#define DXT10_FORMAT_R10G10B10_XR_BIAS_A2_UNORM 89U
#define DXT10_FORMAT_B8G8R8A8_TYPELESS 90U
#define DXT10_FORMAT_B8G8R8A8_UNORM_SRGB 91U
#define DXT10_FORMAT_B8G8R8X8_TYPELESS 92U
#define DXT10_FORMAT_B8G8R8X8_UNORM_SRGB 93U
#define DXT10_FORMAT_BC6H_TYPELESS 94U
#define DXT10_FORMAT_BC6H_UF16 95U
#define DXT10_FORMAT_BC6H_SF16 96U
#define DXT10_FORMAT_BC7_TYPELESS 97U
#define DXT10_FORMAT_BC7_UNORM 98U
#define DXT10_FORMAT_BC7_UNORM_SRGB 99U
#define DXT10_FORMAT_AYUV 100U
#define DXT10_FORMAT_Y410 101U
#define DXT10_FORMAT_Y416 102U
#define DXT10_FORMAT_NV12 103U
#define DXT10_FORMAT_P010 104U
#define DXT10_FORMAT_P016 105U
#define DXT10_FORMAT_420_OPAQUE 106U
#define DXT10_FORMAT_YUY2 107U
#define DXT10_FORMAT_Y210 108U
#define DXT10_FORMAT_Y216 109U
#define DXT10_FORMAT_NV11 110U
#define DXT10_FORMAT_AI44 111U
#define DXT10_FORMAT_IA44 112U
#define DXT10_FORMAT_P8 113U
#define DXT10_FORMAT_A8P8 114U
#define DXT10_FORMAT_B4G4R4A4_UNORM 115U

#define DXT10_FORMAT_P208 130U
#define DXT10_FORMAT_V208 131U
#define DXT10_FORMAT_V408 132U

#define DXT10_DIMENSION_TEXTURE1D 0X00000002U
#define DXT10_DIMENSION_TEXTURE2D 0X00000003U
#define DXT10_DIMENSION_TEXTURE3D 0X00000004U

#define DXT10_RESOURCE_MISC_TEXTURECUBE 0X00000004U