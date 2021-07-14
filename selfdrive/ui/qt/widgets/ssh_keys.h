#pragma once

#include <QPushButton>

#include "selfdrive/hardware/hw.h"
#include "selfdrive/ui/qt/widgets/controls.h"

// SSH enable toggle
class SshToggle : public ToggleControl {
  Q_OBJECT

public:
  SshToggle() : ToggleControl("Enable SSH", "", "", Hardware::get_ssh_enabled()) {
    QObject::connect(this, &SshToggle::toggleFlipped, [=](bool state) {
      Hardware::set_ssh_enabled(state);
    });
  }
};

// SSH key management widget
class SshControl : public ButtonControl {
  Q_OBJECT

public:
  SshControl();

private:
  Params params;

  QLabel username_label;

  void refresh();
  void getUserKeys(const QString &username);
};
// 깃풀관련들 - openpilotusers 참조
class PrebuiltToggle : public ToggleControl {
  Q_OBJECT

public:
  PrebuiltToggle() : ToggleControl("Prebuilt", "Prebuilt 파일을 생성하며 부팅속도를 단축시킵니다. UI수정을 한 경우 기능을 끄십시오.", "../assets/offroad/icon_shell.png", Params().getBool("PutPrebuiltOn")) {
    QObject::connect(this, &PrebuiltToggle::toggleFlipped, [=](int state) {
      char value = state ? '1' : '0';
      Params().put("PutPrebuiltOn", &value, 1);
    });
  }
};

class GpsOffToggle : public ToggleControl {
  Q_OBJECT

public:
  GpsOffToggle() : ToggleControl("화이트판다 only", "화이트판다 사용시 자동종료를 위해서 켜세요", "../assets/offroad/icon_shell.png", Params().getBool("GpsOff")) {
    QObject::connect(this, &GpsOffToggle::toggleFlipped, [=](int state) {
      char value = state ? '1' : '0';
      Params().put("GpsOff", &value, 1);
    });
  }
};

class GitHash : public AbstractControl {
  Q_OBJECT

public:
  GitHash();

private:
  QLabel local_hash;
  QLabel remote_hash;
  Params params;
};
