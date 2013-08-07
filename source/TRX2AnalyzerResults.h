#ifndef TRX2_ANALYZER_RESULTS
#define TRX2_ANALYZER_RESULTS

#include <AnalyzerResults.h>

class TRX2Analyzer;
class TRX2AnalyzerSettings;

class TRX2AnalyzerResults : public AnalyzerResults
{
public:
	TRX2AnalyzerResults( TRX2Analyzer* analyzer, TRX2AnalyzerSettings* settings );
	virtual ~TRX2AnalyzerResults();

	virtual void GenerateBubbleText( U64 frame_index, Channel& channel, DisplayBase display_base );
	virtual void GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id );

	virtual void GenerateFrameTabularText(U64 frame_index, DisplayBase display_base );
	virtual void GeneratePacketTabularText( U64 packet_id, DisplayBase display_base );
	virtual void GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base );

protected: //functions

protected:  //vars
	TRX2AnalyzerSettings* mSettings;
	TRX2Analyzer* mAnalyzer;
};

#endif //TRX2_ANALYZER_RESULTS
