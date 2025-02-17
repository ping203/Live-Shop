#pragma once

#include <atlcoll.h>
#include <IAgoraRtcEngine.h>
#include <map>

#include "AGEngineEventHandler.h"

// #define ENABLE_CODEC	1

using namespace agora::rtc;
using namespace std;

#define AG_ENGFLAG_ENNETTEST	0x00000001
#define AG_ENGFLAG_ECHOTEST		0x00000002
#define AG_ENGFLAG_SPKPHTEST	0x00000004
#define AG_ENGFLAG_MICPHTEST	0x00000008
#define AG_ENGFLAG_VIDEOTEST	0x00000010

#define AG_ENGFLAG_AGCON		0x00000100	// Automatic gain
#define AG_ENGFLAG_NSON			0x00000200	// Noise reduction
#define AG_ENGFLAG_AECON		0x00000400	// Echo Cancellation

#define APP_ID				_T("")

typedef struct _SEI_INFO
{
	UINT	nUID;
	int		nIndex;
	int		x;
	int		y;
	int		nWidth;
	int		nHeight;

} SEI_INFO, *PSEI_INFO, *LPSEI_INFO;

class CAgoraObject
{
public:
	~CAgoraObject(void);
	
	std::map<CString, FRAME_RATE> m_mapFrameRate;

	static CString LoadAppID();

	void SetNetworkTestFlag(BOOL bEnable);
	BOOL GetNetworkTestFlag();

	void SetEchoTestFlag(BOOL bEnable);
	BOOL GetEchoTestFlag();

	void SetSpeakerphoneTestFlag(BOOL bEnable);
	BOOL GetSpeakerphoneTestFlag();

	void SetMicrophoneTestFlag(BOOL bEnable);
	BOOL GetMicrophoneTestFlag();

	void SetVideoTestFlag(BOOL bEnable);
	BOOL GetVideoTestFlag();

	void SetMsgHandlerWnd(HWND hWnd);
	HWND GetMsgHandlerWnd();

	BOOL SetLogFilePath(LPCTSTR lpLogPath = NULL);

	BOOL SetVideoProfile2(int nWidth, int nHeight, int nFrameRate, int nBitRate, BOOL bFineTurn);
	BOOL SetVideoProfileEx(int nWidth, int nHeight, int nFrameRate, int nBitRate);
	BOOL KeepPrerotation(bool bRotate);

	BOOL JoinChannel(LPCTSTR lpChannelName, UINT nUID = 0, LPCSTR lpDynamicKey = NULL);
	BOOL LeaveCahnnel();
	CString GetChanelName();
	CString GetCallID();
	CString GetAppID() { return m_strAppID; };

	void SetAppCert(LPCTSTR lpAppCert) { m_strAppCert = lpAppCert; };
	CString GetAppCert() { return m_strAppCert; };

	void SetSelfUID(UINT nUID) { m_nSelfUID = nUID; };
	UINT GetSelfUID() { return m_nSelfUID; };

	BOOL EnableVideo(BOOL bEnable = TRUE);
	BOOL IsVideoEnabled();

	BOOL EnableScreenCapture(HWND hWnd, int nCapFPS = 15, LPCRECT lpCapRect = NULL, BOOL bEnable = TRUE, int nBitrate = 0);
	BOOL IsScreenCaptureEnabled();

	BOOL MuteLocalAudio(BOOL bMuted = TRUE);
	BOOL IsLocalAudioMuted();

	BOOL MuteAllRemoteAudio(BOOL bMuted = TRUE);
	BOOL IsAllRemoteAudioMuted();

	BOOL MuteRemoteAudio(uid_t uid, BOOL bMuted = TRUE);
	BOOL MuteRemoteVideo(uid_t uid, BOOL bMuted = TRUE);

	BOOL MuteLocalVideo(BOOL bMuted = TRUE);
	BOOL IsLocalVideoMuted();

	BOOL MuteAllRemoteVideo(BOOL bMuted = TRUE);
	BOOL IsAllRemoteVideoMuted();

	BOOL EnableLoopBack(BOOL bEnable = TRUE);
	BOOL IsLoopBackEnabled();

	BOOL SetChannelProfile(BOOL bBroadcastMode);
	BOOL IsBroadcastMode();
	
	void SetWantedRole(CLIENT_ROLE_TYPE role);
	int  GetWnatedRole() { return m_nWantRoleType; };

	BOOL SetClientRole(CLIENT_ROLE_TYPE role, LPCSTR lpPermissionKey = NULL);
	int  GetClientRole() { return m_nRoleType; };

	BOOL EnableAudioRecording(BOOL bEnable, LPCTSTR lpFilePath);

	BOOL EnableLastmileTest(BOOL bEnable = TRUE);

	BOOL LocalVideoPreview(HWND hVideoWnd, BOOL bPreviewOn = TRUE);

	BOOL SetLogFilter(UINT logFilterType, LPCTSTR lpLogPath);

    BOOL SetEncryptionSecret(LPCTSTR lpKey, int nEncryptType = 0);

    BOOL EnableLocalRender(BOOL bEnable);
	BOOL EnableLocalMirrorImage(BOOL bMirrorLocal);


	BOOL EnableWebSdkInteroperability(BOOL bEnable);

    int CreateMessageStream();
    BOOL SendChatMessage(int nStreamID, LPCTSTR lpChatMessage);

	BOOL SetHighQualityAudioPreferences(BOOL bFullBand, BOOL bStereo, BOOL bFullBitrate);
	BOOL StartAudioMixing(LPCTSTR lpMusicPath, BOOL bLoopback, BOOL bReplace, int nCycle);
	BOOL StopAudioMixing();
	BOOL PauseAudioMixing();
	BOOL ResumeAudioMixing();
	
	BOOL EnableAudio(BOOL bEnable);
	BOOL IsAudioEnabled();

	void SetSEIInfo(UINT nUID, LPSEI_INFO lpSEIInfo = NULL);
	void RemoveSEIInfo(UINT nUID);
	void RemoveAllSEIInfo();
	BOOL GetSEIInfo(UINT nUID, LPSEI_INFO lpSEIInfo);
	BOOL GetSEIInfoByIndex(int nIndex, LPSEI_INFO lpSEIInfo);
	int	 GetSEICount() { return m_mapSEIInfo.GetCount(); };
	BOOL EnableSEIPush(BOOL bEnable, COLORREF crBack);

	BOOL EnableH264Compatible();
	BOOL AdjustVolume(int nRcdVol, int nPlaybackVol, int nMixVol);
	void GetVolume(int *nRcdVol, int *nPlaybackVol, int *nMixVol);

	int GetAudioMixingPos();
	int GetAudioMixingDuration();

	void SetSelfResolution(int nWidth, int nHeight);
	void GetSelfResolution(int *nWidth, int *nHeight);

	BOOL EnableExtendAudioCapture(BOOL bEnable, IAudioFrameObserver* lpAudioFrameObserver);
	BOOL EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver);
	BOOL SetAudioProfile(int nSampleRate, int nChannels, int nSamplesPerCall);

	static IRtcEngine *GetEngine();
	
	static CString GetSDKVersion();
	static CString GetSDKVersionEx();
	static BOOL EnableWhiteboardVer(BOOL bEnable);
	static BOOL EnableWhiteboardFeq(BOOL bEnable);
	static CAGEngineEventHandler* getEngineEventHandle();
	static CAgoraMetaDataObserver* getAgoraMetaDataObserver();

	CStringA getDynamicMediaChannelKey(CString channelname);
protected:
	CAgoraObject(void);

private:
	DWORD	m_dwEngineFlag;
	static  CAgoraObject	*m_lpAgoraObject;
	static	IRtcEngine		*m_lpAgoraEngine;
	static	CString			m_strAppID;

	CString					m_strAppCert;
	
	UINT		m_nSelfUID;
	CString		m_strChannelName;
	BOOL		m_bVideoEnable;
	BOOL		m_bAudioEnable;

	BOOL		m_bLocalAudioMuted;
	BOOL		m_bLocalVideoMuted;
	BOOL		m_bAllRemoteAudioMuted;
	BOOL		m_bAllRemoteVideoMuted;
	BOOL		m_bScreenCapture;

	int			m_nWantRoleType;
	int			m_nRoleType;
	int			m_nChannelProfile;

	int			m_nRcdVol;
	int			m_nPlaybackVol;
	int			m_nMixVol;

	BOOL		m_bLoopBack;
	BOOL		m_bFullBand;
	BOOL		m_bStereo;
	BOOL		m_bFullBitrate;

	int			m_nCanvasWidth;
	int			m_nCanvasHeight;

	CAtlMap<UINT, SEI_INFO>	m_mapSEIInfo;

	CString					m_strDynamicChannelKey;

public:
	static CAgoraObject *GetAgoraObject(LPCTSTR lpVendorKey = NULL);
	static void CloseAgoraObject();

	static CAGEngineEventHandler m_EngineEventHandler;
	static CAgoraMetaDataObserver m_metaDataObserver;
};
