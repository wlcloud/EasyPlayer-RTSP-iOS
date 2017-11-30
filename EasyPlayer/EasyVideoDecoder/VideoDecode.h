

#ifndef _VideoDecode_h
#define _VideoDecode_h

#ifdef __cplusplus
extern "C" {
#endif
    
// 算法类型
typedef enum {
    CODER_MPEG4,
    CODER_H264
}Coder;

typedef enum {
    IDM_SW = 0,
    IDM_GLSL,
}IDECODE_METHODE;
    
#define MAX_PLANES  3
    
typedef unsigned char   BYTE;
    
// should be entirely filled by all codecs
typedef struct DVDVideoPicture {
    union {
        struct {
            BYTE* data[4];      // [4] = alpha channel, currently not used
            int iLineSize[4];   // [4] = alpha channel, currently not used
        };
    };
    
    unsigned int iFlags;
    
    double       iRepeatPicture;
    double       iDuration;
    unsigned int iFrameType         : 4; // see defines above // 1->I, 2->P, 3->B, 0->Undef
    unsigned int color_matrix       : 4;
    unsigned int color_range        : 1; // 1 indicate if we have a full range of color
    unsigned int chroma_position;
    unsigned int color_primaries;
    unsigned int color_transfer;
    unsigned int extended_format;
    int iGroupId;
    
    unsigned char* qscale_table; // Quantization parameters, primarily used by filters
    int qscale_stride;
    int qscale_type;
    
    unsigned int iWidth;
    unsigned int iHeight;
    unsigned int iDisplayWidth;  // width of the picture without black bars
    unsigned int iDisplayHeight; // height of the picture without black bars
    
    enum EFormat {
        FMT_YUV420P = 0,
        FMT_VDPAU,
        FMT_NV12,
        FMT_UYVY,
        FMT_YUY2,
        FMT_DXVA,
        FMT_VAAPI,
        FMT_OMXEGL,
        FMT_CVBREF,
    } format;
}DVDVideoPicture;
    

// 创建参数
typedef struct _DEC_CREATE_PARAM {
    int nMaxImgWidth;
    int nMaxImgHeight;
    Coder coderID;
    IDECODE_METHODE method;

}DEC_CREATE_PARAM;

// 解码参数
typedef struct _DEC_DECODE_PARAM {
    int nLen; 
    unsigned char *pStream;  
    unsigned char *pImgRGB;     // 解码得出的RGB数据[in]
    int nOutWidth;
    int nOutHeight;
    int nLineSize;
    int need_sps_head;
    unsigned char *yuv[4];
    int linsize[4];
}DEC_DECODE_PARAM;       
    
void DecodeRegiestAll();
void *DecodeCreate(DEC_CREATE_PARAM *pCreateParam);

unsigned int DecodeVideo(void *DecHandle, DEC_DECODE_PARAM *pDecodeParam, DVDVideoPicture *picture);
void DecodeClose(void *DecHandle);
    
#ifdef __cplusplus
}
#endif

#endif
