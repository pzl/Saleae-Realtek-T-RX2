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
	void GenStartCode();
	void GenCommandCode(U32 opcode);

	SimulationChannelDescriptor mX2SimulationData;

};

enum CommandCode { FORWARD = 10, FORWARD_TURBO=16, TURBO=22, FORWARD_LEFT=28, FORWARD_RIGHT=34, BACKWARD=40, BACKWARD_RIGHT=46, BACKWARD_LEFT=52, LEFT=58, RIGHT=64 };

#endif //TRX2_SIMULATION_DATA_GENERATOR