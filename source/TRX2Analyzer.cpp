#include "TRX2Analyzer.h"
#include "TRX2AnalyzerSettings.h"
#include <AnalyzerChannelData.h>

TRX2Analyzer::TRX2Analyzer()
:	Analyzer(),  
	mSettings( new TRX2AnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

TRX2Analyzer::~TRX2Analyzer()
{
	KillThread();
}

void TRX2Analyzer::WorkerThread()
{
	mResults.reset( new TRX2AnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );

	mSampleRateHz = GetSampleRate();

	mData = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mData->GetBitState() == BIT_LOW )
		mData->AdvanceToNextEdge();


	

/*
	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1 << 7;
		
		mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit

		U64 starting_sample = mSerial->GetSampleNumber();

		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{
			//let's put a dot exactly where we sample this bit:
			mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

			if( mSerial->GetBitState() == BIT_HIGH )
				data |= mask;

			mSerial->Advance( samples_per_bit );

			mask = mask >> 1;
		}


		//we have a byte to save. 
		Frame frame;
		frame.mData1 = data;
		frame.mFlags = 0;
		frame.mStartingSampleInclusive = starting_sample;
		frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

		mResults->AddFrame( frame );
		mResults->CommitResults();
		ReportProgress( frame.mEndingSampleInclusive );
	}
	*/
}

bool TRX2Analyzer::NeedsRerun()
{
	return false;
}

U32 TRX2Analyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 TRX2Analyzer::GetMinimumSampleRateHz()
{
	return 8000;
}

const char* TRX2Analyzer::GetAnalyzerName() const
{
	return "Realtek T/RX2";
}

const char* GetAnalyzerName()
{
	return "Realtek T/RX2";
}

Analyzer* CreateAnalyzer()
{
	return new TRX2Analyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}