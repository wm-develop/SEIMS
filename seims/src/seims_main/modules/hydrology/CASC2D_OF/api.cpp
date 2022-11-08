#include "api.h"

#include "CASC2D_OF.h"
#include "text.h"
#include "MetadataInfo.h"

extern "C" SEIMS_MODULE_API SimulationModule* GetInstance() {
    return new CASC2D_OF();
}

/// function to return the XML Metadata document string
extern "C" SEIMS_MODULE_API const char* MetadataInformation() {
    MetadataInfo mdi;

    mdi.SetAuthor("Liangjun Zhu");
    mdi.SetClass("TEST", "Functionality test of the module template!");
    mdi.SetDescription("Template of SEIMS module");
    mdi.SetID("CASC2D_OF");
    mdi.SetName("CASC2D_OF");
    mdi.SetVersion("1.0");
    mdi.SetEmail(SEIMS_EMAIL);
    mdi.SetWebsite(SEIMS_SITE);
    mdi.SetHelpfile("");

    /// Set parameters from database (Source_ParameterDB or Source_ParameterDB_Optional)

    /// Parameters with basic data types
    //mdi.AddParameter("SingleValueParam", "UNIT", "DESC", Source_ParameterDB, DT_Single);
    //mdi.AddParameter("OptioanlParam", "UNIT", "DESC", Source_ParameterDB_Optional, DT_Single);
    //mdi.AddParameter("1DArrayParam", "UNIT", "DESC", Source_ParameterDB, DT_Array1D);
    //mdi.AddParameter("1DRasterParam", "UNIT", "DESC", Source_ParameterDB, DT_Raster1D);
    //mdi.AddParameter("2DArrayParam", "UNIT", "DESC", Source_ParameterDB, DT_Array2D);
    //mdi.AddParameter("2DRasterParam", "UNIT", "DESC", Source_ParameterDB, DT_Raster2D);

    /// Parameters with complex data types
	mdi.AddParameter(VAR_DEM, UNIT_NON_DIM, DESC_DEM, Source_ParameterDB, DT_Raster1D);
	mdi.AddParameter(VAR_MANNING, UNIT_NON_DIM, DESC_MANNING, Source_ParameterDB, DT_Raster1D);
	mdi.AddParameter(Tag_HillSlopeTimeStep, UNIT_SECOND, DESC_DT_HS, File_Input, DT_Single);
	mdi.AddParameter(Tag_CellWidth, UNIT_LEN_M, DESC_CellWidth, Source_ParameterDB, DT_Single);
	mdi.AddParameter(VAR_STREAM_LINK, UNIT_NON_DIM, DESC_STREAM_LINK, Source_ParameterDB, DT_Raster1D);
	mdi.AddParameter(Tag_FLOWOUT_INDEX_D8, UNIT_NON_DIM, DESC_FLOWOUT_INDEX_D8, Source_ParameterDB, DT_Array1D);
	//暂时初始化为0，不从外部读入
	//mdi.AddParameter(VAR_SUR_SDEP, UNIT_DEPTH_MM, DESC_SUR_SDEP, Source_ParameterDB, DT_Array1D);
	mdi.AddParameter(REACH_DEPTH, UNIT_NON_DIM, DESC_REACH_DEPTH_SPATIAL, Source_ParameterDB, DT_Raster1D);
	mdi.AddParameter(Type_RasterPositionData, UNIT_NON_DIM, DESC_RasterPositionData, Source_ParameterDB, DT_Raster1D);

	/// Set inputs from other modules (Source_Module or Source_Module_Optional)

	//mdi.AddInput(VAR_EXCP, UNIT_DEPTH_MM, DESC_EXCP, Source_Module, DT_Raster1D); //Excess precipitation 过量降水，可形成洼地蓄水或地表径流
	//mdi.AddInput(VAR_NEPR, UNIT_DEPTH_MM, DESC_NEPR, Source_Module, DT_Raster1D);
	//mdi.AddInput(VAR_CH_V, UNIT_SPEED_MS, DESC_CH_V, Source_Module, DT_Raster1D);
	mdi.AddInput(VAR_SURU, UNIT_DEPTH_MM, DESC_SURU, Source_Module, DT_Raster1D);

    /// Set output variables of the current module
	mdi.AddOutput(VAR_QOVERLAND, UNIT_FLOW_CMS, DESC_QOVERLAND, DT_Raster1D);
	mdi.AddOutput(VAR_OUTLET_Q, UNIT_FLOW_CMS, DESC_OUTLET_Q, DT_Single);
	mdi.AddOutput(VAR_OUTLET_V, UNIT_VOL_M3, DESC_OUTLET_V, DT_Single);
	mdi.AddOutput(VAR_SURU, UNIT_DEPTH_MM, DESC_SURU, DT_Raster1D);
	mdi.AddOutput(VAR_CH_WRT_DEPTH, UNIT_DEPTH_MM, DESC_CH_WRT_DEPTH, DT_Raster1D);
    /// Set In/Output variables with transferred data type


    /// Write out the XML file.
    string res = mdi.GetXMLDocument();
    char* tmp = new char[res.size() + 1];
    strprintf(tmp, res.size() + 1, "%s", res.c_str());
    return tmp;
}
