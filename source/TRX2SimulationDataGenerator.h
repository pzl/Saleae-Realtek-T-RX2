#ifndef TRX2_SIMULATION_DATA_GENERATOR
#define TRX2_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class TRX2AnalyzerSettings;

class TRX2SimulationDataGenerator
{
public:
	TRX2SimulationDataGenerator();
	~TRX2SimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, TRX2AnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	TRX2AnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void MakeFakeData();
	void StartCode();
	void CommandCode(U32 opcode);

	SimulationChannelDescriptor mX2SimulationData;

};
#endif //TRX2_SIMULATION_DATA_GENERATOR