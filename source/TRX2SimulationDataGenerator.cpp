#include "TRX2SimulationDataGenerator.h"
#include "TRX2AnalyzerSettings.h"

#include <AnalyzerHelpers.h>

TRX2SimulationDataGenerator::TRX2SimulationDataGenerator()
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
	mX2SimulationData.SetInitialBitState( BIT_LOW );
}

U32 TRX2SimulationDataGenerator::GenerateSimulationData( U64 largest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel )
{
	U64 adjusted_largest_sample_requested = AnalyzerHelpers::AdjustSimulationTargetSample( largest_sample_requested, sample_rate, mSimulationSampleRateHz );

	while( mX2SimulationData.GetCurrentSampleNumber() < adjusted_largest_sample_requested )
	{
		MakeFakeData();
	}

	*simulation_channel = &mX2SimulationData;
	return 1;
}

void TRX2SimulationDataGenerator::MakeFakeData()
{
	//we're currenty low
	//let's move forward a little
	mX2SimulationData.Advance( mSimulationSampleRateHz * .003 );
	
	GenCommandCode(FORWARD);
	GenCommandCode(FORWARD_LEFT);
	GenCommandCode(FORWARD);
	GenCommandCode(FORWARD_RIGHT);
	
}

void TRX2SimulationDataGenerator::GenCommandCode(U32 opcode)
{
	GenStartCode();
	for (U32 i=0; i<opcode; i++){
		mX2SimulationData.TransitionIfNeeded(BIT_HIGH);
		mX2SimulationData.Advance(mSimulationSampleRateHz * .000333);
		mX2SimulationData.Transition();
		mX2SimulationData.Advance(mSimulationSampleRateHz * .00033);
	}
}

void TRX2SimulationDataGenerator::GenStartCode()
{
	for (U32 i=0; i<4; i++){
		mX2SimulationData.TransitionIfNeeded(BIT_HIGH);
		mX2SimulationData.Advance(mSimulationSampleRateHz * .001);
		mX2SimulationData.Transition();
		mX2SimulationData.Advance(mSimulationSampleRateHz * .00033);
	}
}
