#ifndef OPTIONS_H
#define OPTIONS_H

class Options : public MSettings
{
  public:
    struct Property
    {
      static Q_DECL_CONSTEXPR auto MinimizeToTray = "minimizeToTray";
    };

             Options();
    virtual ~Options() Q_DECL_OVERRIDE Q_DECL_EQ_DEFAULT;

    bool minimizeToTray() const;
};

extern MLazySingleton<Options> gOptions;

#endif