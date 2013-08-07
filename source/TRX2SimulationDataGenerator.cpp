#include "TRX2SimulationDataGenerator.h"
#include "TRX2AnalyzerSettings.h"

#include <AnalyzerHelpers.h>

TRX2SimulationDataGenerator::TRX2SimulationDataGenerator()
:	mDataText( "My first analyzer, woo hoo!" ),
	mStringIndex( 0 )
{
}

TRX2SimulationDataGenerator::~TRX2SimulationDataGenerator()
{
}

void TRX2SimulationDataGenerator::Initialize( U32 simulation_sample_rate, TRX2AnalyzerSettings* settings )
{
	mSimulationSampleRateHz = simulation_sample_rate;
	mSettings = settings;

	mX2SimulationData.SetChannel( mSettings->mInputChannel );
	mX2SimulationData.SetSampleRate( simulation_sample_rate );
	mX2SimulationData.SetInitialBitState( BIT_HIGH );
}

U32 TRX2SimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mX2SimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		CreateSerialByte();
	}

	*simulation_channel = &mX2SimulationData;
	return 1;
}

void TRX2SimulationDataGenerator::CreateSerialByte()
{
	U32 samples_per_bit = mSimulationSampleRateHz / 8000;

	U8 byte = mDataText[ mStringIndex ];
	mStringIndex++;
	if( mStringIndex == mDataText.size() )
		mStringIndex = 0;

	//we're currenty high
	//let's move forward a little
	mX2SimulationData.Advance( samples_per_bit * 10 );

	mX2SimulationData.Transition();  //low-going edge for start bit
	mX2SimulationData.Advance( samples_per_bit );  //add start bit time

	U8 mask = 0x1 << 7;
	for( U32 i=0; i<8; i++ )
	{
		if( ( byte & mask ) != 0 )
			mX2SimulationData.TransitionIfNeeded( BIT_HIGH );
		else
			mX2SimulationData.TransitionIfNeeded( BIT_LOW );

		mX2SimulationData.Advance( samples_per_bit );
		mask = mask >> 1;
	}

	mX2SimulationData.TransitionIfNeeded( BIT_HIGH ); //we need to end high

	//lets pad the end a bit for the stop bit:
	mX2SimulationData.Advance( samples_per_bit );
}
