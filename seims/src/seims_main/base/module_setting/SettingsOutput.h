/*!
 * \brief Setting Outputs for SEIMS
 * \author Junzhi Liu, LiangJun Zhu
 * \version 2.0
 * \date May 2017
 * \revised LJ - Refactor, decoupling with database IO
 */
#ifndef SEIMS_SETTING_OUTPUT_H
#define SEIMS_SETTING_OUTPUT_H

#include "utilities.h"
#include "Settings.h"
#include "PrintInfo.h"

#include "MongoUtil.h"
#include "clsRasterData.h"

/*!
 * \ingroup module_setting
 * \struct OrgOutItem
 */
struct OrgOutItem {
public:
    OrgOutItem() : modCls(""), outputID(""), descprition(""), outFileName(""),
                   aggType(""), unit(""), subBsn(""), intervalUnit(""), sTimeStr(""),
                   eTimeStr(""), interval(-1), use(-1) {};
    ~OrgOutItem() = default;
public:
    string modCls;
    string outputID;
    string descprition;
    string outFileName;
    string aggType;
    string unit;
    string subBsn;
    string intervalUnit;
    string sTimeStr;
    string eTimeStr;
    int interval;
    int use;
};
/*!
 * \ingroup module_setting
 * \class SettingsOutput
 * \brief 
 */
class SettingsOutput : public Settings, private NotCopyable {
public:
    /*!
     * \brief Constructor
     * \param[in] subbasinNum Subbasin number of the entire watershed
     * \param[in] outletID The subbasin ID of outlet
     * \param[in] subbasinID Current subbasin ID, 0 for OMP version
     * \param[in] outputItems Vector of original output items read from FILE_OUT file (or table)
     */
    SettingsOutput(int subbasinNum, int outletID, int subbasinID, vector<OrgOutItem> &outputItems);

    //! Destructor
    virtual ~SettingsOutput();

    //! Init function
    static SettingsOutput *Init(int subbasinNum, int outletID, int subbasinID, vector<OrgOutItem> &outputItems);

    //! Write output information to log file
    virtual void Dump(string& filename);

    //! Check date of output settings
    void checkDate(time_t, time_t);

public:
    //! All the print settings
    vector<PrintInfo *> m_printInfos;
    /*!
     * \brief All the output settings
     * key: OutputID
     * value: \sa PrintInfo instance
     */
    map<string, PrintInfo *> m_printInfosMap;

private:
    //! number of subbasins
    int m_nSubbasins;
    //! subbasin ID which outlet located
    int m_outletID;
    //! current subbasin ID, 0 for OMP version
    int m_subbasinID;
};
#endif /* SEIMS_SETTING_OUTPUT_H */
