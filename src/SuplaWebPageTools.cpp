#include "SuplaWebPageTools.h"
#include "SuplaDeviceGUI.h"

void createWebTools() {
  WebServer->httpServer.on(getURL(PATH_TOOLS), handleTools);

  WebServer->httpServer.on(getURL(PATH_FACTORY_RESET), [&]() {
    if (ConfigESP->configModeESP == NORMAL_MODE) {
      if (!WebServer->httpServer.authenticate(WebServer->www_username, WebServer->www_password))
        return WebServer->httpServer.requestAuthentication();
    }
    WebServer->httpServer.sendHeader("Location", "/");
    WebServer->httpServer.send(303);
    WebServer->sendContent(WebServer->supla_webpage_start(0));
    ConfigESP->factoryReset(true);
  });
}

void handleTools() {
  if (ConfigESP->configModeESP == NORMAL_MODE) {
    if (!WebServer->httpServer.authenticate(WebServer->www_username, WebServer->www_password))
      return WebServer->httpServer.requestAuthentication();
  }

  String content = "";
  addFormHeader(content, "Tools");
  //#ifdef SUPLA_BUTTON
  addButton(content, "Save config", PATH_DOWNLOAD);
  //#endif
  //#ifdef SUPLA_BUTTON
  addButton(content, "Load config", PATH_UPLOAD);
  //#endif
#ifdef SUPLA_OTA
  addButton(content, S_UPDATE, PATH_UPDATE_HENDLE);
#endif
  addButton(content, "Factory reset", PATH_FACTORY_RESET);
  addFormHeaderEnd(content);
  addButton(content, S_RETURN, "");

  WebServer->sendContent(content);
}