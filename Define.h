#define AUTO_PC						//AUTO_PCビルド時に必要
//#define DATA_SQL					//SQL使用時に必要(CDROM時にはコメントにすること)
#define DATA_CDROM					//CDROM使用時に必要

//-------------版数------------------------------
#define DEF_VERSION				L"ver.0.29"
//-------------Menu関連------------------------------
#define DEF_MENU_ROUTE			10
#define DEF_MENU_ROUTE_START	11
#define DEF_MENU_ROUTE_STOP		12
#define DEF_MENU_ROUTING		13
#define DEF_MENU_REROUTING		14
#define DEF_MENU_ROUTE_CLR		15
#define DEF_MENU_START_DEMO		16
#define DEF_MENU_STOP_DEMO		17
//-------------MyMap関連------------------------------
#define DEF_MAYMAP_PASSWORD		L"0"				//パスワード
#define FILE_MYMAP				L"MyMap.Dat"		//ファイル
//#define FILE_MYMAP_MEMO			L"MyMap%03d.Dat"	//memoファイル

//#define FOLDER_MYMAP_INFO		L"\\MyMapInfo\\"	//infoデータフォルダ

//-------------ﾙｰﾄ検索関連------------------------------
//#define DEF_NODE_MAX			12000			//ノード最大数
//#define DEF_NODE_CONNECT_MAX	18000			//接続最大数
#define DEF_NODE_MAX			14000			//ノード最大数
#define DEF_NODE_CONNECT_MAX	20000			//接続最大数
//#define DEF_NODE_MAX			14			//ノード最大数
//#define DEF_NODE_CONNECT_MAX	20			//接続最大数

#define DEF_NODE_FILE			L"Node1.Dat"	//位置情報ファイル
#define DEF_NODE_CONNECT_FILE	L"Node2.Dat"	//接続情報ファイル
#define DEF_LINK_IDX_FILE		L"LINK.IDX"		//ノード間描画情報インデックスファイル
#define DEF_LINK_DAT_FILE		L"LINK.DAT"		//ノード間描画情報データファイル
#define DEF_ONEWAY_FILE			L"OneWay.DAT"	//一方通行データファイル

//-------------動作国------------------------------
#define COUNTRY_USA				0
#define COUNTRY_KOREA			1
//--------------ファイルフォルダ(自動判定)------------------------------------
#define DATA_PATH_1ST			L"\\Storage Card\\"
#define DATA_PATH_2ND			L"\\ﾒﾓﾘ ｶｰﾄﾞ\\"
#define DATA_PATH_3RD			L"\\CNS\\"
//--------------RS232C速度------------------------------------
//#define COM_SPEED				CBR_9600
#define COM_SPEED				CBR_4800
#define COM_RECEIVE_BUF_SIZE	4096
//--------------描画可能最大数------------------------------------
//#define BODY_ROAD_MAX			2000
#define BODY_ROAD_MAX			1500
//#define BODY_ICON_MAX			200
#define BODY_ICON_MAX			150
#define BODY_TEXT_MAX			150
//#define BODY_TEXT_MAX			100
//#define BODY_POLY_MAX			500
#define BODY_POLY_MAX			400
//#define BODY_POLY_POINT_MAX	200
#define BODY_POLY_POINT_MAX		300
//#define BODY_LINE_MAX			200
#define BODY_LINE_MAX			100
//--------------環境ファイル------------------------------------------------------------
//#define DEFAULT_START_EW_USA	-118.333333333333
//#define DEFAULT_START_NS_USA	34.083333333333
#define DEFAULT_START_EW_USA -115.16666666666
#define DEFAULT_START_NS_USA   36.16666666666
#define DEFAULT_START_EW_KOREA	126.98599
#define DEFAULT_START_NS_KOREA	37.55895
//#define DEFAULT_START_EW_KOREA	126.5146444
//#define DEFAULT_START_NS_KOREA	33.5016583
#define FILE_START_EN			L"Env.dat"
//--------------軌跡ファイル----------------------------------------------------------
#define FILE_DRAIVE_LOG			L"DriveLog.dat"
//--------------IPファイル----------------------------------------------------------
#define FILE_IP_ADR				L"IPADR.dat"
//-------------------------------------------------------------------------------------
#define SLEEP_232C_CLOSE		2000
#define REDRAW_ANGLE			20
//--------------カラーコード------------------------------------------------------------
#define DEFAULT_BACKCOLOR		RGB(255,255,162)			//背景色
#define COLOR_MAPMACH			248							//マップマッチ色			　赤
//#define COLOR_MAPMACH			RGB(255,0,0)				//マップマッチ色			　赤
#define COLOR_ROUTE_MAPMACH		64760					//ルート検索時マップマッチ色　黄
//#define COLOR_ROUTE_MAPMACH		RGB(255,255,0)				//ルート検索時マップマッチ色　黄

//------------------------------------------------------------------------
#define DEF_CONVERT				10000000.0
#define SEARCH_STRING_MAX		100
//------------------周辺検索サーバ------------------------------------------------------
//#define SEARCH1_SAVER_IP		L"192.168.0.104"			//MM
//#define SEARCH1_SAVER_IP		L"172.21.133.254"			//YOKOCHI
#define SEARCH1_SAVER_IP		L"211.188.18.23"			//SRC
#define SEARCH1_SAVER_PORT		2004
//------------------ID検索サーバ------------------------------------------------------
//#define SEARCH_ID_SAVER_IP		L"172.21.133.254"			//YOKOCHI
#define SEARCH_ID_SAVER_IP		L"211.188.18.23"			//SRC
#define SEARCH_ID_SAVER_PORT	2006
//------------------ルート検索サーバ------------------------------------------------------
//#define SEARCH2_SAVER_IP		L"192.168.0.101"			//MM
//#define SEARCH2_SAVER_IP		L"172.21.133.139"			//YOKOCHI
#define SEARCH2_SAVER_IP		L"211.188.18.23"			//SRC
#define SEARCH2_SAVER_PORT		2002

//------------------RASエントリ名------------------------------------------------------
#define RAS_NEWENTRY			L"NewEntry"
//#define RAS_PHONENO			L"9,8360347"
//#define RAS_USERNAME			L"abc"
//#define RAS_PASSWORD			L"1"
#define RAS_PHONENO				L"1"
#define RAS_USERNAME			L"mogi"
#define RAS_PASSWORD			L"1515"
//--------------データファイル------------------------------------------------------------
#define FILE_DAT_ROAD3			L"ROAD3.DAT"
#define FILE_IDX_ROAD3			L"ROAD3.IDX"
#define FILE_DAT_ROAD6			L"ROAD6.DAT"
#define FILE_IDX_ROAD6			L"ROAD6.IDX"
#define FILE_DAT_ROAD9			L"ROAD9.DAT"
#define FILE_IDX_ROAD9			L"ROAD9.IDX"

#define FILE_DAT_ICON1			L"ICON1.DAT"
#define FILE_IDX_ICON1			L"ICON1.IDX"
#define FILE_DAT_ICON2			L"ICON2.DAT"
#define FILE_IDX_ICON2			L"ICON2.IDX"
#define FILE_DAT_ICON3			L"ICON3.DAT"
#define FILE_IDX_ICON3			L"ICON3.IDX"
#define FILE_DAT_ICON4			L"ICON4.DAT"
#define FILE_IDX_ICON4			L"ICON4.IDX"
#define FILE_DAT_ICON5			L"ICON5.DAT"
#define FILE_IDX_ICON5			L"ICON5.IDX"
#define FILE_DAT_ICON6			L"ICON6.DAT"
#define FILE_IDX_ICON6			L"ICON6.IDX"
#define FILE_DAT_ICON7			L"ICON7.DAT"
#define FILE_IDX_ICON7			L"ICON7.IDX"
#define FILE_DAT_ICON8			L"ICON8.DAT"
#define FILE_IDX_ICON8			L"ICON8.IDX"
#define FILE_DAT_ICON9			L"ICON9.DAT"
#define FILE_IDX_ICON9			L"ICON9.IDX"
#define FILE_DAT_ICON10			L"ICON10.DAT"
#define FILE_IDX_ICON10			L"ICON10.IDX"

#define FILE_DAT_TEXT1			L"TEXT1.DAT"
#define FILE_IDX_TEXT1			L"TEXT1.IDX"
#define FILE_DAT_TEXT2			L"TEXT2.DAT"
#define FILE_IDX_TEXT2			L"TEXT2.IDX"
#define FILE_DAT_TEXT3			L"TEXT3.DAT"
#define FILE_IDX_TEXT3			L"TEXT3.IDX"
#define FILE_DAT_TEXT4			L"TEXT4.DAT"
#define FILE_IDX_TEXT4			L"TEXT4.IDX"
#define FILE_DAT_TEXT5			L"TEXT5.DAT"
#define FILE_IDX_TEXT5			L"TEXT5.IDX"
#define FILE_DAT_TEXT6			L"TEXT6.DAT"
#define FILE_IDX_TEXT6			L"TEXT6.IDX"
#define FILE_DAT_TEXT7			L"TEXT7.DAT"
#define FILE_IDX_TEXT7			L"TEXT7.IDX"
#define FILE_DAT_TEXT8			L"TEXT8.DAT"
#define FILE_IDX_TEXT8			L"TEXT8.IDX"
#define FILE_DAT_TEXT9			L"TEXT9.DAT"
#define FILE_IDX_TEXT9			L"TEXT9.IDX"
#define FILE_DAT_TEXT10			L"TEXT10.DAT"
#define FILE_IDX_TEXT10			L"TEXT10.IDX"

#define FILE_DAT_POLY3			L"POLY3.DAT"
#define FILE_IDX_POLY3			L"POLY3.IDX"
#define FILE_RNK_POLY3			L"POLY3.RANK"
#define FILE_DAT_POLY6			L"POLY6.DAT"
#define FILE_IDX_POLY6			L"POLY6.IDX"
#define FILE_RNK_POLY6			L"POLY6.RANK"
#define FILE_DAT_POLY9			L"POLY9.DAT"
#define FILE_IDX_POLY9			L"POLY9.IDX"
#define FILE_RNK_POLY9			L"POLY9.RANK"

#define FILE_DAT_LINE3			L"LINE3.DAT"
#define FILE_IDX_LINE3			L"LINE3.IDX"
#define FILE_DAT_LINE6			L"LINE6.DAT"
#define FILE_IDX_LINE6			L"LINE6.IDX"
#define FILE_DAT_LINE9			L"LINE9.DAT"
#define FILE_IDX_LINE9			L"LINE9.IDX"

//#define FILE_DAT_TURN			L"TURN.DAT"
//#define FILE_IDX_TURN			L"TURN.IDX"
//#define FILE_DAT_NODE			L"NODE.DAT"
//#define FILE_IDX_NODE			L"NODE.IDX"
//#define FILE_DAT_AREALINK		L"AREALINK.DAT"
//#define FILE_IDX_AREALINK		L"AREALINK.IDX"
//#define FILE_DAT_LINK			L"LINK.DAT"
//#define FILE_IDX_LINK			L"LINK.IDX"
#define FILE_DAT_NAME			L"NAME.DAT"
#define FILE_IDX_NAME			L"NAME.IDX"

//--------------ルート設定ファイル------------------------------------------------------------
#define FILE_ROUTE				L"ROUTE.BIN"
//--------------demoファイル------------------------------------------------------------
#define DEMO_FILE_GPS			L"DEMO_NMEA.GPS"
#define DEMO_FILE_ROUTE			L"DEMO_ROUTE.BIN"
//--------------音声ファイル------------------------------------------------------------
#define WAV_ROUTE_OUT			L"jpn_Outroute.wav"
//#define WAV_ROUTE_IN			L"apcAlarm3.wav"
#define WAV_STRAIGHT_700		L"700_12.wav"
#define WAV_LITTLE_RIGHT_700	L"jpn_little-right700.wav"
#define WAV_LITTLE_LEFT_700		L"jpn_little-left700.wav"
#define WAV_RIGHT_700			L"jpn_right700.wav"
#define WAV_LEFT_700			L"jpn_left700.wav"
//#define WAV_U_TURN_700			L"700_U.wav"
//#define WAV_END_700				L"apcEnd700.wav"
#define WAV_STRAIGHT			L"jpn_Straight.wav"
#define WAV_LITTLE_RIGHT		L"jpn_little-right.wav"
#define WAV_LITTLE_LEFT			L"jpn_little-left.wav"
#define WAV_RIGHT				L"jpn_right.wav"
#define WAV_LEFT				L"jpn_left.wav"
//#define WAV_U_TURN				L"300_U.wav"
#define WAV_END					L"jpn_END.WAV"
//#define WAV_UNKNOWN				L"unknown.wav"
/*
#define WAV_STRAIGHT_700		L"700_12.wav"
#define WAV_LITTLE_RIGHT_700	L"700_1.wav"
#define WAV_LITTLE_LEFT_700		L"700_10.wav"
#define WAV_RIGHT_700			L"700_RT.wav"
#define WAV_LEFT_700			L"700_LT.wav"
#define WAV_U_TURN_700			L"700_U.wav"
//#define WAV_END_700				L"apcEnd700.wav"
#define WAV_STRAIGHT			L"12.wav"
#define WAV_LITTLE_RIGHT		L"1.wav"
#define WAV_LITTLE_LEFT			L"10.wav"
#define WAV_RIGHT				L"RT.wav"
#define WAV_LEFT				L"LT.wav"
#define WAV_U_TURN				L"U.wav"
#define WAV_END					L"GOAL.wav"
*/
//--------------住所検索フォルダ and ファイル------------------------------------------------------------
#define FILE_ADR_FOLDER			L"adr\\"
#define FILE_ADR_FILE_TOP		L"adrs.dat"
//--------------カテゴリ検索フォルダ and ファイル------------------------------------------------------------
#define FILE_CATEGORY_FOLDER	L"item\\"
#define FILE_CATEGORY_AREA		L"area.dat"	//地域一覧
#define FILE_CATEGORY_G1		L"g1.dat"	//大分類一覧
//--------------INFOファイル------------------------------------------------------------
#define FILE_INFO_IDX			L"info.idx"
#define FILE_INFO_DAT			L"info.dat"
//--------音声判定角度--------------------------------------------------
#define DEF_WAV_STRAIGHT		22		//以下直進(ゴール地点用)
#define DEF_WAV_LITTLE_TURN		45		//以下やや曲がる(負は左方向)
#define DEF_WAV_TURN			90		//以下曲がる(負は左方向)

#define DEF_STRAIGHT			0		//直進
#define DEF_LEFT_LITTLE			1		//やや左
#define DEF_RIGHT_LITTLE		2		//やや右
#define DEF_LEFT				3		//左
#define DEF_RIGHT				4		//右

//--------TRACE--------------------------------------------------
#define TRACE_WARNING		1							//HlpTRACE用警告
#define TRACE_ERR			2							//HlpTRACE用ｴﾗｰ
#define TRACE_DEBUG			3							//HlpTRACE用debug
//--------状態フラグ---------------------------------------------------
#define ST_ITEM_MAX			9	//状態フラグ数
#define ST_RUN				0	//通常走行中
#define ST_SCROLL			1	//スクロールモード
#define ST_ROUTE_OUT		2	//ルートがはずれた
#define ST_MAPMACH_VIEW		3	//マップマッチ画面表示(debug用)
#define ST_ROUTE_NODE_VIEW	4	//ルート検索ノード表示(debug用)
#define ST_GPS_TRACE		5	//GPS情報トレース(debug用)
#define ST_WAIT				6	//WAIT DLG表示中
//#define ST_SAVE_ROUTE_DATA	7	//ルート検索データ保存(debug用)
//#define ST_SET_ROUTE_DATA	8	//ルート検索データ設定(debug用)

//--------------画面サイズ------------------------------------------------------------
//#define DISP_CX				400
//#define DISP_CY				234
#define DISP_CX				240
#define DISP_CY				268
//--------------バファサイズ------------------------------------------------------------
#define	BUF_SIZE			32000
//--------------ﾒｯｾｰｼﾞ------------------------------------------------------------
#define	WM_TRACE			WM_USER+201			//HlpTRACE用
#define WM_EVENT			WM_USER+500
#define WM_DLG_CLOSE		WM_USER+401
//--------------ｲﾝﾃﾞｯｸｽ------------------------------------------------------------
//#define IDX_DLG_MENU		101
//#define IDX_DLG_TRACE		102
//#define IDX_DLG_SEARCH		103
//#define IDX_DLG_SEARCH2		104
#define IDX_DLG_SEARCH_ID	105
//#define IDX_DLG_MAP_LEVEL	106
#define IDX_DLG_ROUTE		107
#define IDX_DLG_DIAL		108
#define IDX_DLG_RAS_ENTRY	109



//#define IDX_DLG_WAIT		110
#define IDX_DLG_INFO		111


//--------------ソケットリクエスト種別------------------------------------------------------------
#define SOC_REQ_G1					1
#define SOC_REQ_G2					2
#define SOC_REQ_G1_G2				3
#define SOC_REQ_SEARCH2_G2			4
#define SOC_REQ_SEARCH2_ROUTE		5
#define SOC_REQ_SEARCH2_ROUTE_USER	6
#define SOC_SEND_ID					7
#define SOC_REQ_SEARCH_ID			8
#define SOC_REQ_REROUTE				9

//------------------ｲﾍﾞﾝﾄ--------------------------------------------------------
#define	EV_SOC_CONNECT				1
#define	EV_SOC_CLOSE				2
#define	EV_LOOPBACK_ON				3
#define	EV_LOOPBACK_OFF				4
#define	EV_SND						6
#define	EV_PASSWORD					7
//#define	EV_SCROLL					8					//画面スクロール
#define	EV_APP_EXIT					9					//終了
#define	EV_START_DEMO				10					//DEMO開始
#define	EV_STOP_DEMO				11					//DEMO停止
#define	EV_STEP_DEMO				12					//DEMO開始

#define EV_GPS_RECEIVE_START		13					//GPS受信開始
#define EV_GPS_RECEIVE_STOP			14					//GPS受信停止

#define EV_T1_TO					101					//ﾀｲﾏ1ﾀｲﾑｱｳﾄ
#define EV_T2_TO					102					//ﾀｲﾏ2ﾀｲﾑｱｳﾄ
#define EV_T3_TO					103					//ﾀｲﾏ3ﾀｲﾑｱｳﾄ
#define EV_T4_TO					104					//ﾀｲﾏ4ﾀｲﾑｱｳﾄ
#define EV_T5_TO					105					//ﾀｲﾏ5ﾀｲﾑｱｳﾄ
#define EV_T6_TO					106					//ﾀｲﾏ6ﾀｲﾑｱｳﾄ
#define EV_T7_TO					107					//ﾀｲﾏ7ﾀｲﾑｱｳﾄ
#define EV_T8_TO					108					//ﾀｲﾏ8ﾀｲﾑｱｳﾄ
#define EV_T9_TO					109					//ﾀｲﾏ9ﾀｲﾑｱｳﾄ


#define EV_SOC_RECEIVE_NOTIF		205					//ｿｹｯﾄ受信通知
#define EV_SOC_CONNECT_NOTIF		206					//ｿｹｯﾄ接続確定通知
#define EV_ACCEPT_NOTIFI			207					//ｿｹｯﾄ接続受領通知
#define	EV_RECEIVE_NOTIFI			241					//受信通知
#define	EV_SEND_NOTIFI				242					//送信通知
#define EV_232C_ON_RECEIVE			243					//GPS受信通知
#define EV_MAP_LEVEL				244					//MAPレベル変更
#define EV_MAP_LEVEL_FORCE			245					//MAPレベル強制変更
#define EV_JUMP_EWNS				247					//指定緯度経度位置へ移動
#define EV_TRACE					248					//
#define EV_INIT						249					//
#define EV_SEARCH					250					//検索
#define EV_SEARCH2					251					//検索
#define EV_SEARCH_ID				252					//ID検索
#define EV_BAKCOLOR					253					//背景色
#define EV_TRCAE_DLG				254					//TRACE DLG
//#define EV_MENU_FOCUS				255
#define EV_VVIEW4					256					//VView4表示切替
#define EV_FUNCKEY					257
#define EV_KEY_DOWN					258
#define EV_WAIT_ENABLE				259
#define EV_WAIT_DISABLE				260
#define EV_THREAD_END				270					//描画スレッド終了通知
//#define EV_ROUTE					271					//ROUTE
#define EV_LOG_CLR					272
#define EV_SET_DIAL					273					//ダイヤル設定
#define EV_DIAL						274					//ダイヤル
#define EV_TEST						275					//TEST
#define EV_RAS						276					//RAS接続切断
#define EV_MENU_CLOSE				277					//メニュークローズ要求

#define EV_0						300					//イベント0
#define EV_1						301					//イベント1
#define EV_2						302					//イベント2
#define EV_3						203					//イベント3
#define EV_4						304					//イベント4
#define EV_5						305					//イベント5
#define EV_6						306					//イベント6
#define EV_7						307					//イベント7
#define EV_8						308					//イベント8
#define EV_9						309					//イベント9
#define EV_10						310					//イベント10




//------------------ﾊﾞﾌｧｻｲｽﾞ--------------------------------------------------------
//#define BUF_SIZE			1024000
//------------------ﾕｰｻﾞ登録ﾊﾟｽﾜｰﾄﾞ--------------------------------------------------------
//#define PASSWORD	"asdfghjk"
//------------------ﾚｼﾞｽﾄﾘ--------------------------------------------------------
//#define REGI_INDEX		"INDEX"
//#define REGI_PASSWORD	"PASSWORD"


//	enum{BUFLEN	= 1024000};								//ﾊﾞﾌｧｻｲｽﾞ


