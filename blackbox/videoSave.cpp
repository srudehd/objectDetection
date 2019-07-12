#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvcam.h>

CVideoWrite::CVideoWrite( HWND* a_hwnd, const char *a_szPath)
{
    m_nVideoWidth = 320;
    m_nVideoHeight = 240;

    SaveFileName( a_szPath );

    CameraInit( a_hwnd );
}

bool CVideoWrite::SaveFileName( const char *a_szPath)
{
    char szFilePath[255] = { 0, };
    char szFullFilePath[2048] = { 0, };
    COleDateTime mdiStart;
    CvSize imgSize;

    imgSize.width = 320;
    imgSize.height = 240;

    char pszEndPathWord[2];
    memset( pszEndPathWord, 0, sizeof( pszEndPathWord) );

    int nPathLen = strlen( a_szPath);

    if( nPathLen == 0)
    {
        AfxMessageBox( L"경로가 입력되지 않았습니다." );
        return false;
    }

    mdiStart = COleDateTime::
}




typedef struct CvVideoWriter cvVideoWriter;

class CVideoWrite
{
public:
    CVideoWrite( HWND *a_hwnd, const char* a_szPath);
    ~CVideoWrite(void)    

public:
    static void cvcamCallBack( IpIImage *a_pstImage);

    void SetVideoSize( int a_nVideoWidth, int a_nVideoHeight)
    {
        m_nVideoWidth = a_nVideoWidth;
        m_nVideoHeight = a_nVideoHeight;
    }
private:
    bool CameraInit( HWND *a_hwnd );

    void CameraDestroy( void );

    bool SaveFileName( const char* a_szPath );

private:
    static CvVideoWriter* m_pVideoWrite;

    int m_nVideoWidth;
    int m_nVideoHeight;
    
};