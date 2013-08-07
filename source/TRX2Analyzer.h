#ifndef TRX2_ANALYZER_H
#define TRX2_ANALYZER_H

#include <Analyzer.h>
#include "TRX2AnalyzerResults.h"
#include "TRX2SimulationDataGenerator.h"

class TRX2AnalyzerSettings;
class ANALYZER_EXPORT TRX2Analyzer : public Analyzer
{
public:
	TRX2Analyzer();
	virtual ~TRX2Analyzer();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< TRX2AnalyzerSettings > mSettings;
	std::auto_ptr< TRX2AnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	TRX2SimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //TRX2_ANALYZER_H
