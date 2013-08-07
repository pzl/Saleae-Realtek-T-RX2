#include "TRX2AnalyzerSettings.h"
#include <AnalyzerHelpers.h>


TRX2AnalyzerSettings::TRX2AnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL ),
	mIsTX( false )
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Alpha", "Bravo" );
	mInputChannelInterface->SetChannel( mInputChannel );

	mIsTXInterface.reset( new AnalyzerSettingInterfaceNumberList() );
	mIsTXInterface->SetTitleAndTooltip( "Charlie",  "Delta" );
	mIsTXInterface->AddNumber(0, "Echo", "Foxtrot");
	mIsTXInterface->AddNumber(1, "Golf", "Hotel");
	mIsTXInterface->SetNumber( mIsTX );

	AddInterface( mInputChannelInterface.get() );
	AddInterface( mIsTXInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "India", false );
}

TRX2AnalyzerSettings::~TRX2AnalyzerSettings()
{
}

bool TRX2AnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mIsTX = mIsTXInterface->GetNumber();

	ClearChannels();
	AddChannel( mInputChannel, "Juliette", true );

	return true;
}

void TRX2AnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mIsTXInterface->SetNumber( mIsTX );
}

void TRX2AnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mIsTX;

	ClearChannels();
	AddChannel( mInputChannel, "Kilo", true );

	UpdateInterfacesFromSettings();
}

const char* TRX2AnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mIsTX;

	return SetReturnString( text_archive.GetString() );
}
