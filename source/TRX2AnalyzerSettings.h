#ifndef TRX2_ANALYZER_SETTINGS
#define TRX2_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class TRX2AnalyzerSettings : public AnalyzerSettings
{
public:
	TRX2AnalyzerSettings();
	virtual ~TRX2AnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	bool mIsTX;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceNumberList >	mIsTXInterface;
};

#endif //TRX2_ANALYZER_SETTINGS
