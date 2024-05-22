#include "espWifiConfig.h"

espWifiConfig::espWifiConfig(DNSServer *dnsServer, WebServer *server)
    : _apIP(192, 168, 4, 1)
{
  _dnsServer = dnsServer;
  _server = server;
}

 

espWifiConfig::~espWifiConfig()
{
}
void espWifiConfig::ui_handler_register(ui_handler_cb *handler)
{
  uihandler = handler;
}
// 用于配置WiFi
void espWifiConfig::wifiConfigured()
{
  initSoftAP();
  initDNS();
  initWebServer();
  scanWifi();
}
// 初始化AP模式
void espWifiConfig::initSoftAP()
{
  WiFi.mode(WIFI_AP);                                           // 配置为AP模式
  WiFi.softAPConfig(_apIP, _apIP, IPAddress(255, 255, 255, 0)); // 设置AP热点IP和子网掩码

  if (WiFi.softAP(_ap_SSID.c_str()))
  { // 开启AP热点,如需要密码则添加第二个参数
    // 打印相关信息
    Serial.println("ESP32S SoftAP is right.");
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
    Serial.println(String("MAC address = ") + WiFi.softAPmacAddress().c_str());
  }
  else
  { // 开启热点失败
    Serial.println("WiFiAP Fai_led_PIN");
    delay(1000);
    Serial.println("restart now...");
    ESP.restart(); // 重启复位esp32
  }
}

// 初始化DNS服务器
void espWifiConfig::initDNS()
{
  // 判断将所有地址映射到esp32的ip上是否成功,DNS端口53
  if (_dnsServer->start(53, "*", _apIP))
  {
    Serial.println("start dnsserver success.");
  }
  else
  {
    Serial.println("start dnsserver fai_led_PIN.");
  }
}

// 初始化WebServer
void espWifiConfig::initWebServer()
{
  // 给设备设定域名esp32,完整的域名是esp32.local
  if (MDNS.begin("esp32"))
  {
    Serial.println("MDNS responder started");
  }
  // 必须添加第二个参数HTTP_GET，以下面这种格式去写，否则无法强制门户
  //  当浏览器请求服务器根目录(网站首页)时调用自定义函数handleRoot处理，设置主页回调函数，必须添加第二个参数HTTP_GET，否则无法强制门户
  _server->on("/", HTTP_GET, [this]()
              { handleRoot(); });
  //  当浏览器请求服务器/configwifi(表单字段)目录时调用自定义函数handleConfigWifi处理
  _server->on("/configwifi", HTTP_POST, [this]()
              { handleConfigWifi(); });
  // 当浏览器请求的网络资源无法在服务器找到时调用自定义函数handleNotFound处理
  _server->onNotFound([this]()
                      { handleNotFound(); });
  // Tells the server to begin listening for incoming connections.Returns None
  _server->begin(); // 启动TCP SERVER
  // _server->setNoDelay(true);                                  //关闭延时发送
  Serial.println("WebServer started!");
}

void espWifiConfig::handleRoot()
{
  // 处理网站根目录“/”(首页)的访问请求,将显示配置wifi的HTML页面
  if (_server->hasArg("selectSSID"))
  {
    _server->send(200, "text/html", ROOT_HTML + _scanNetworksID + "</body></html>");
  }
  else
  {
    _server->send(200, "text/html", ROOT_HTML + _scanNetworksID + "</body></html>");
  }
}

void espWifiConfig::handleConfigWifi()
{
  // 提交数据后，返回给客户端信息函数
  // 返回http状态
  // _server->send(200, "text/html", SUCCESS_HTML);
  if (_server->hasArg("ssid"))
  { // 判断是否有账号参数
    Serial.print("got ssid:");
    _wifi_ssid = _server->arg("ssid"); // 获取html表单输入框name名为"ssid"的内容
    // strcpy(sta_ssid, _server->arg("ssid").c_str());//将账号参数拷贝到sta_ssid中
    Serial.println(_wifi_ssid);
  }
  else
  { // 没有参数
    Serial.println("error, not found ssid");
    _server->send(200, "text/html", "<meta charset='UTF-8'>error, not found ssid"); // 返回错误页面
    return;
  }
  // 密码与账号同理
  if (_server->hasArg("pass"))
  {
    Serial.print("got password:");
    _wifi_pass = _server->arg("pass"); // 获取html表单输入框name名为"pwd"的内容
    // strcpy(sta_pass, _server->arg("pass").c_str());
    Serial.println(_wifi_pass);
  }
  else
  {
    Serial.println("error, not found password");
    _server->send(200, "text/html", "<meta charset='UTF-8'>error, not found password");
    return;
  }
  _server->send(200, "text/html", "<meta charset='UTF-8'>SSID：" + _wifi_ssid + "<br />password：" + _wifi_pass + "<br />已取得WiFi信息,正在尝试连接,请手动关闭此页面。"); // 返回保存成功页面

 
    if (uihandler->tip_message != NULL)
    {
      uihandler->tip_message("已取得WiFi信息,正在尝试连接......");
    }
  delay(2000);
  WiFi.softAPdisconnect(true); // 参数设置为true，设备将直接关闭接入点模式，即关闭设备所建立的WiFi网络。
  _server->close();            // 关闭web服务
  WiFi.softAPdisconnect();     // 在不输入参数的情况下调用该函数,将关闭接入点模式,并将当前配置的AP热点网络名和密码设置为空值.
  Serial.println("WiFi Connect SSID:" + _wifi_ssid + "  PASS:" + _wifi_pass);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("开始调用连接函数connectToWiFi()..");
    connectToWifi(); // 进入配网阶段
  }
  else
  {
    Serial.println("Connected wifi success!..");
    Serial.println("提交的配置信息自动连接成功..");
  }
}
void espWifiConfig::handleNotFound()
{
  // 设置处理404情况的函数'handleNotFound'
  // 当浏览器请求的网络资源无法在服务器找到时通过此自定义函数处理
  // 访问不存在目录则返回配置页面
  handleRoot();
  //   _server->send(404, "text/plain", "404: Not found");
}

// 扫描WiFi
bool espWifiConfig::scanWifi()
{
  Serial.println("scan start");
  // 扫描附近WiFi
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
  {
    Serial.println("no networks found");
    _scanNetworksID = "no networks found";
    return false;
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      _scanNetworksID += "<P>" + WiFi.SSID(i) + "</P>";
      delay(10);
    }
    return true;
  }
}

void espWifiConfig::connectToWifi()
{
  Serial.println("进入connectToWiFi()函数");
  // 设置为STA模式并连接WIFI
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(true); // 设置自动连接
  // 用字符串成员函数c_str()生成一个const char*指针，指向以空字符终止的数组,即获取该字符串的指针。
  if (_wifi_ssid != "")
  {
    Serial.println("用web配置信息连接.");

    WiFi.begin(_wifi_ssid.c_str(), _wifi_pass.c_str());
    _wifi_ssid = "";
    _wifi_pass = "";
  }
  else
  {
    Serial.println("用nvs保存的信息连接.");
    WiFi.begin(); // 连接上一次连接成功的wifi
  }
  // WiFi.begin(_wifi_ssid.c_str(), _wifi_pass.c_str());
  int Connect_time = 0; // 用于连接计时，如果长时间连接不成功，复位设备
  while (WiFi.status() != WL_CONNECTED)
  { // 等待WIFI连接成功
    Serial.print(".");
    digitalWrite(_led_PIN, !digitalRead(_led_PIN));
    delay(500);
    Connect_time++;
    if (Connect_time > 2 * _timeOut_s)
    { // 长时间连接不上，重新进入配网页面
      digitalWrite(_led_PIN, LOW);
      Serial.println("");
      Serial.println("WIFI autoconnect fail, start AP for webconfig now...");
      wifiConfigured(); // 转到网页端手动配置wifi
      return;           // 跳出 防止无限初始化
    }
  }
  if (WiFi.status() == WL_CONNECTED)
  {
     if (uihandler == NULL)
    {
       Serial.println("uihandler is  NULL!");
      return;
    }

    if (uihandler->tip_message != NULL)
    {
      uihandler->tip_message("WIFI连接成功！......");
    }
   if (uihandler->ui_handelr != NULL)
    {
      uihandler->ui_handelr(WL_CONNECTED);
    }
    Serial.println("WIFI connect Success");
    Serial.printf("SSID:%s", WiFi.SSID().c_str());
    Serial.printf(", PSW:%s\r\n", WiFi.psk().c_str());
    Serial.print("LocalIP:");
    Serial.print(WiFi.localIP());
    Serial.print(" ,GateIP:");
    Serial.print(WiFi.gatewayIP());

    IPAddress dnsServer = WiFi.dnsIP();
    Serial.print(" ,DNS Server:");
    Serial.println(dnsServer);
    Serial.print("WIFI status is:");
    Serial.println(WiFi.status());
    digitalWrite(_led_PIN, HIGH);
    _server->stop();
  }
}

// _led_PIN闪烁,_led_PIN为脚号,n为次数,t为时间间隔ms
void blink_led_PIN(int _led_PIN, int n, int t)
{
  for (int i = 0; i < 2 * n; i++)
  {
    digitalWrite(_led_PIN, !digitalRead(_led_PIN));
    delay(t);
  }
}

// 删除保存的wifi信息,并使_led_PIN闪烁5次
void espWifiConfig::restoreWifi()
{
  delay(500);
  esp_wifi_restore(); // 删除保存的wifi信息
  Serial.println("连接信息已清空,准备重启设备..");
  delay(10);
  blink_led_PIN(_led_PIN, 5, 500); // _led_PIN闪烁5次
  digitalWrite(_led_PIN, LOW);
}

void espWifiConfig::checkConnect(bool reConnect)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WIFI未连接.");
    //  Serial.println(WiFi.status());
    if (digitalRead(_led_PIN) != LOW)
    {
      digitalWrite(_led_PIN, LOW);
    }
    if (reConnect == true && WiFi.getMode() != WIFI_AP && WiFi.getMode() != WIFI_AP_STA)
    {
      Serial.println("WIFI未连接.");
      Serial.println("WiFi Mode:");
      Serial.println(WiFi.getMode());
      Serial.println("正在连接WiFi...");
    
      if (uihandler != NULL && uihandler->tip_message != NULL)
      {
        uihandler->tip_message("正在连接WiFi......");
      }

      connectToWifi();
    }
  }
  else if (digitalRead(_led_PIN) != HIGH)
  {
    digitalWrite(_led_PIN, HIGH);
  }
}
