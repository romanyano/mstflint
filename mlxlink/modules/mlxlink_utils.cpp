/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 *
 */

#include "mlxlink_utils.h"

using namespace std;

u_int32_t findMaxKey(std::vector<std::string> keys)
{
    u_int32_t maxKeySize = 0;
    for (std::vector<std::string>::iterator it = keys.begin(); it != keys.end();
         ++it) {
        if ((*it).length() > maxKeySize) {
            maxKeySize = (*it).length();
        }
    }
    return maxKeySize;
}

std::string convertIntToHexString(int toConvert)
{
    std::stringstream hexStr;
    hexStr << std::hex << toConvert;
    return hexStr.str();
}

string deleteLastComma(string &s)
{
    if (s.size()) {
        s.erase(s.size() - 1);
    }
    return s;
}

std::string getStringFromVector(std::vector<std::string> values)
{
    std::string s;
    for (std::vector<std::string>::const_iterator i = values.begin();
         i != values.end(); ++i) {
        s += *i + ',';
    }
    return deleteLastComma(s);
}

std::string getStringFromVector(std::vector<float> values)
{
    std::string s;
    for (std::vector<float>::const_iterator i = values.begin();
         i != values.end(); ++i) {
        s += to_string(*i) + ',';
    }
    return deleteLastComma(s);
}

u_int64_t add32BitTo64(u_int32_t value1, u_int32_t value2)
{
    return (((u_int64_t) value1) << 32 | value2);
}

string status2Color(u_int32_t status)
{
    return (status == 0 || status == 1023) ? ANSI_COLOR_GREEN : ANSI_COLOR_RED;
}

string getLoopbackColor(u_int32_t loopbackMode)
{
    switch (loopbackMode) {
    case PHY_NO_LOOPBACK:
        return ANSI_COLOR_GREEN;
        break;

    case PHY_REMOTE_LOOPBACK:
        return ANSI_COLOR_CYAN;
        break;

    case PHY_LOCAL_LOOPBACK:
        return ANSI_COLOR_BLUE;
        break;

    case EXTERNAL_LOCAL_LOOPBACK:
        return ANSI_COLOR_MAGENTA;

    default:
        return ANSI_COLOR_RED;
    }
    return ANSI_COLOR_RED;
}

string getAnDisableColor(u_int32_t anDisable)
{
    switch (anDisable) {
    case AN_DISABLE_NORMAL:
        return ANSI_COLOR_GREEN;

    case AN_DISABLE_FORCE:
        return ANSI_COLOR_BLUE;

    default:
        return ANSI_COLOR_RED;
    }
}

string IBSupportedSpeeds2Str(u_int32_t mask)
{
    string maskStr = "";

    if (mask & IB_LINK_SPEED_HDR) {
        maskStr += "HDR,";
    }
    if (mask & IB_LINK_SPEED_EDR) {
        maskStr += "EDR,";
    }
    if (mask & IB_LINK_SPEED_FDR) {
        maskStr += "FDR,";
    }
    if (mask & IB_LINK_SPEED_FDR10) {
        maskStr += "FDR10,";
    }
    if (mask & IB_LINK_SPEED_QDR) {
        maskStr += "QDR,";
    }
    if (mask & IB_LINK_SPEED_DDR) {
        maskStr += "DDR,";
    }
    if (mask & IB_LINK_SPEED_SDR) {
        maskStr += "SDR,";
    }

    return deleteLastComma(maskStr);
}

string EthSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";

    if ((int_mask & ETH_LINK_SPEED_100G_CR4) || (int_mask & ETH_LINK_SPEED_100G_KR4) || (int_mask & ETH_LINK_SPEED_100G_SR4) || (int_mask & ETH_LINK_SPEED_100G_LR4)) {
        maskStr += "100G,";
    }
    if ((int_mask & ETH_LINK_SPEED_56G_R4) || (int_mask & ETH_LINK_SPEED_56G_CR4) || (int_mask & ETH_LINK_SPEED_56G_KR4)) {
        maskStr += "56G,";
    }
    if ((int_mask & ETH_LINK_SPEED_50G_CR2) || (int_mask & ETH_LINK_SPEED_50G_KR2) || (int_mask & ETH_LINK_SPEED_50G_SR2) || (int_mask & ETH_LINK_SPEED_50G_KR4)) {
        maskStr += "50G,";
    }
    if ((int_mask & ETH_LINK_SPEED_40G_CR4) || (int_mask & ETH_LINK_SPEED_40G_KR4) || (int_mask & ETH_LINK_SPEED_40G_SR4) || (int_mask & ETH_LINK_SPEED_40G_LR4)) {
        maskStr += "40G,";
    }
    if ((int_mask & ETH_LINK_SPEED_25G_CR) || (int_mask & ETH_LINK_SPEED_25G_KR) || (int_mask & ETH_LINK_SPEED_25G_SR)) {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_20G_KR2) {
        maskStr += "20G,";
    }
    if ((int_mask & ETH_LINK_SPEED_10G_CR) || (int_mask & ETH_LINK_SPEED_10G_KR) || (int_mask & ETH_LINK_SPEED_10G_SR) || (int_mask & ETH_LINK_SPEED_10G_LR) || (int_mask & ETH_LINK_SPEED_10G_CX4) || (int_mask & ETH_LINK_SPEED_10G_KX4) || (int_mask & ETH_LINK_SPEED_10G_BaseT)) {
        maskStr += "10G,";
    }
    if ((int_mask & ETH_LINK_SPEED_1000_SGMII) || (int_mask & ETH_LINK_SPEED_1000_KX) || (int_mask & ETH_LINK_SPEED_1000_BaseT)) {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_100_BaseTx) {
        maskStr += "100";
    }

    return deleteLastComma(maskStr);
}

string EthExtSupportedSpeeds2Str(u_int32_t int_mask)
{
    string maskStr = "";

    if (int_mask & ETH_LINK_SPEED_EXT_400GAUI_8) {
        maskStr += "400G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_200GAUI_4) {
        maskStr += "200G,";
    }
    if ((int_mask & ETH_LINK_SPEED_EXT_100GAUI_2) || (int_mask & ETH_LINK_SPEED_EXT_CAUI_4)) {
        maskStr += "100G,";
    }
    if ((int_mask & ETH_LINK_SPEED_EXT_50GAUI_1) || (int_mask & ETH_LINK_SPEED_EXT_50GAUI_2)) {
        maskStr += "50G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XLAUI_4) {
        maskStr += "40G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_25GAUI_1) {
        maskStr += "25G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_XFI) {
        maskStr += "10G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_5GBASE_R) {
        maskStr += "5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_2_5GBASE_X) {
        maskStr += "2.5G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_1000BASE_X) {
        maskStr += "1G,";
    }
    if (int_mask & ETH_LINK_SPEED_EXT_SGMII_100M) {
        maskStr += "100";
    }

    return deleteLastComma(maskStr);
}

string SupportedSpeeds2Str(u_int32_t proto_active, u_int32_t mask, bool extended)
{
    if(extended) {
        return EthExtSupportedSpeeds2Str(mask);
    }
    return proto_active == IB ?
           IBSupportedSpeeds2Str(mask) : EthSupportedSpeeds2Str(mask);
}

string getOui(u_int32_t oui)
{
    string ouiStr;
    switch (oui) {
    case OTHER:
        ouiStr = "Other";
        break;

    case MELLANOX:
        ouiStr = "Mellanox";
        break;

    case KNOWN_OUI:
        ouiStr = "Known OUI";
        break;

    default:
        ouiStr = "Other";
    }
    return ouiStr;
}

int ptysSpeedToExtMaskETH(const string & speed)
{
    if(speed == "200G")
        return ETH_LINK_SPEED_EXT_200GAUI_4;
    if(speed == "400G")
        return ETH_LINK_SPEED_EXT_400GAUI_8;
    return 0x0;
}

int ptysSpeedToMaskETH(const string &speed)
{
    if (speed == "1G") {
        return (ETH_LINK_SPEED_1000_SGMII | ETH_LINK_SPEED_1000_KX
                | ETH_LINK_SPEED_1000_BaseT);
    }
    if (speed == "10G") {
        return (ETH_LINK_SPEED_10G_CX4 | ETH_LINK_SPEED_10G_KX4
                | ETH_LINK_SPEED_10G_CR | ETH_LINK_SPEED_10G_KR
                | ETH_LINK_SPEED_10G_LR | ETH_LINK_SPEED_10G_SR
                | ETH_LINK_SPEED_10G_BaseT);
    }
    if (speed == "20G") {
        return ETH_LINK_SPEED_20G_KR2;
    }
    if (speed == "40G") {
        return (ETH_LINK_SPEED_40G_CR4 | ETH_LINK_SPEED_40G_KR4
                | ETH_LINK_SPEED_40G_LR4 | ETH_LINK_SPEED_40G_SR4);
    }
    if (speed == "56G") {
        return (ETH_LINK_SPEED_56G_CR4 | ETH_LINK_SPEED_56G_KR4
                | ETH_LINK_SPEED_56G_R4);
    }
    if (speed == "50G") {
        return (ETH_LINK_SPEED_50G_CR2 | ETH_LINK_SPEED_50G_KR2
                | ETH_LINK_SPEED_50G_SR2 | ETH_LINK_SPEED_50G_KR4);
    }
    if (speed == "100G") {
        return (ETH_LINK_SPEED_100G_CR4 | ETH_LINK_SPEED_100G_KR4
                | ETH_LINK_SPEED_100G_LR4 | ETH_LINK_SPEED_100G_SR4);
    }
    if (speed == "100") {
        return ETH_LINK_SPEED_100_BaseTx;
    }
    if (speed == "25G") {
        return (ETH_LINK_SPEED_25G_CR | ETH_LINK_SPEED_25G_KR
                | ETH_LINK_SPEED_25G_SR);
    }
    return 0x0;
}

int ptysSpeedToMaskIB(const string &speed)
{
    if (speed == "SDR") {
        return IB_LINK_SPEED_SDR;
    }
    if (speed == "DDR") {
        return IB_LINK_SPEED_DDR;
    }
    if (speed == "QDR") {
        return IB_LINK_SPEED_QDR;
    }
    if (speed == "FDR10") {
        return IB_LINK_SPEED_FDR10;
    }
    if (speed == "FDR") {
        return IB_LINK_SPEED_FDR;
    }
    if (speed == "EDR") {
        return IB_LINK_SPEED_EDR;
    }
    if (speed == "HDR") {
        return IB_LINK_SPEED_HDR;
    }
    return 0x0;
}

bool checkPaosCmd(const string &paosCmd)
{
    if (paosCmd != "UP" && paosCmd != "DN" && paosCmd != "TG") {
        return false;
    }
    return true;
}

bool checkPepcForceMode(const string &forceMode)
{
    if (forceMode != "MA" && forceMode != "SL") {
        return false;
    }
    return true;
}

bool checkPepcANMode(const string &anMode)
{
    if (anMode != "AU" && anMode != "MA" && anMode != "SL") {
        return false;
    }
    return true;
}

bool checkPplmCmd(const string &pplmCmd)
{
    if (pplmCmd != "AU" && pplmCmd != "NF" && pplmCmd != "FC"
        && pplmCmd != "RS") {
        return false;
    }
    return true;
}

bool checkPplrCmd(const string &pplrCmd)
{
    if (pplrCmd != "NO" && pplrCmd != "PH" && pplrCmd != "EX") {
        return false;
    }
    return true;
}

int prbsModeToMask(const string &mode)
{
    if (mode == "PRBS31") {
        return PRBS31;
    }
    if (mode == "PRBS23A") {
        return PRBS23A;
    }
    if (mode == "PRBS23B") {
        return PRBS23B;
    }
    if (mode == "PRBS23C") {
        return PRBS23C;
    }
    if (mode == "PRBS23D") {
        return PRBS23D;
    }
    if (mode == "PRBS7") {
        return PRBS7;
    }
    if (mode == "PRBS11") {
        return PRBS11;
    }
    if (mode == "PRBS11A") {
        return PRBS11A;
    }
    if (mode == "PRBS11B") {
        return PRBS11B;
    }
    if (mode == "PRBS11C") {
        return PRBS11C;
    }
    if (mode == "PRBS11D") {
        return PRBS11D;
    }
    if (mode == "PRBS9") {
        return PRBS9;
    }
    if (mode == "IDLE") {
        return IDLE;
    }
    return PRBS31;
}

string prbsMaskToMode(u_int32_t mask)
{
    if (mask == PRBS31) {
        return "PRBS31";
    }
    if (mask == PRBS23A) {
        return "PRBS23A";
    }
    if (mask == PRBS23B) {
        return "PRBS23B";
    }
    if (mask == PRBS23C) {
        return "PRBS23C";
    }
    if (mask == PRBS23D) {
        return "PRBS23D";
    }
    if (mask == PRBS7) {
        return "PRBS7";
    }
    if (mask == PRBS11) {
        return "PRBS11";
    }
    if (mask == PRBS11A) {
        return "PRBS11A";
    }
    if (mask == PRBS11B) {
        return "PRBS11B";
    }
    if (mask == PRBS11C) {
        return "PRBS11C";
    }
    if (mask == PRBS11D) {
        return "PRBS11D";
    }
    if (mask == PRBS9) {
        return "PRBS9";
    }
    if (mask == IDLE) {
        return "IDLE";
    }
    return "N/A";
}

int prbsModeCapToMask(const string &mode)
{
    if (mode == "PRBS31") {
        return PRBS31_CAP;
    }
    if (mode == "PRBS23A") {
        return PRBS23A_CAP;
    }
    if (mode == "PRBS23B") {
        return PRBS23B_CAP;
    }
    if (mode == "PRBS23C") {
        return PRBS23C_CAP;
    }
    if (mode == "PRBS23D") {
        return PRBS23D_CAP;
    }
    if (mode == "PRBS7") {
        return PRBS7_CAP;
    }
    if (mode == "PRBS11") {
        return PRBS11_CAP;
    }
    if (mode == "PRBS11A") {
        return PRBS11A_CAP;
    }
    if (mode == "PRBS11B") {
        return PRBS11B_CAP;
    }
    if (mode == "PRBS11C") {
        return PRBS11C_CAP;
    }
    if (mode == "PRBS11D") {
        return PRBS11D_CAP;
    }
    if (mode == "PRBS9") {
        return PRBS39_CAP;
    }
    if (mode == "IDLE") {
        return PRBSIDLE_CAP;
    }
    return PRBS31_CAP;
}

bool prbsModeCheck(const string &mode)
{
    if (mode == "PRBS31") {
        return true;
    }
    if (mode == "PRBS23A") {
        return true;
    }
    if (mode == "PRBS23B") {
        return true;
    }
    if (mode == "PRBS23C") {
        return true;
    }
    if (mode == "PRBS23D") {
        return true;
    }
    if (mode == "PRBS7") {
        return true;
    }
    if (mode == "PRBS11") {
        return true;
    }
    if (mode == "PRBS11A") {
        return true;
    }
    if (mode == "PRBS11B") {
        return true;
    }
    if (mode == "PRBS11C") {
        return true;
    }
    if (mode == "PRBS11D") {
        return true;
    }
    if (mode == "PRBS9") {
        return true;
    }
    if (mode == "IDLE") {
        return true;
    }
    return false;
}

int prbsLaneRateToMask(const string &rate)
{
    if (rate == "IB-SDR" || rate == "SDR") {
        return PRBS_SDR;
    }
    if (rate == "IB-DDR" || rate == "DDR" || rate == "5G" || rate == "5GbE") {
        return PRBS_DDR;
    }
    if (rate == "IB-QDR" || rate == "QDR") {
        return PRBS_QDR;
    }
    if (rate == "IB-FDR10" || rate == "FDR10" || rate == "10G" || rate == "10GbE" || rate == "40G" || rate == "40GbE") {
        return PRBS_FDR10;
    }
    if (rate == "IB-FDR" || rate == "FDR" || rate == "14G" || rate == "14GbE") {
        return PRBS_FDR;
    }
    if (rate == "IB-EDR" || rate == "EDR" || rate == "25G" || rate == "25GbE" || rate == "50G" || rate == "50GbE" || rate == "100G" || rate == "100GbE") {
        return PRBS_EDR;
    }
    if (rate == "IB-HDR" || rate == "HDR" || rate == "200GbE" || rate == "200G" || rate == "400G" || rate == "400GbE") {
        return PRBS_HDR;
    }
    if (rate == "1G" || rate == "1GbE") {
        return PRBS_1G;
    }
    if (rate == "XAUI" || rate == "2.5G" || rate == "2.5GbE") {
        return PRBS_XAUI;
    }
    if (rate == "50GE-KR4" || rate == "12.89G" || rate == "12.89GbE") {
        return PRBS_50G;
    }
    return PRBS_EDR;
}

string prbsMaskToLaneRate(u_int32_t mask)
{
    if (mask == PRBS_SDR) {
        return "2.5G";
    }
    if (mask == PRBS_DDR) {
        return "5G";
    }
    if (mask == PRBS_QDR) {
        return "10G";
    }
    if (mask == PRBS_FDR10) {
        return "10.3125G";
    }
    if (mask == PRBS_FDR) {
        return "14.0625G";
    }
    if (mask == PRBS_EDR) {
        return "25.78125G";
    }
    if (mask == PRBS_HDR) {
        return "53.125G";
    }
    if (mask == PRBS_1G) {
        return "1.25G";
    }
    if (mask == PRBS_XAUI) {
        return "3.125G";
    }
    if (mask == PRBS_50G) {
        return "12.89G";
    }
    return "N/A";
}

int prbsLaneRateCapToMask(const string &rate)
{
    if (rate == "IB-SDR" || rate == "SDR") {
        return LANE_RATE_SDR_CAP;
    }
    if (rate == "IB-DDR" || rate == "DDR" || rate == "5G" || rate == "5GbE") {
        return LANE_RATE_DDR_CAP;
    }
    if (rate == "IB-QDR" || rate == "QDR") {
        return LANE_RATE_QDR_CAP;
    }
    if (rate == "IB-FDR10" || rate == "FDR10" || rate == "10G" || rate == "10GbE" || rate == "40G" || rate == "40GbE") {
        return LANE_RATE_FDR10_CAP;
    }
    if (rate == "IB-FDR" || rate == "FDR" || rate == "14G" || rate == "14GbE") {
        return LANE_RATE_FDR_CAP;
    }
    if (rate == "IB-EDR" || rate == "EDR" || rate == "25G" || rate == "25GbE" || rate == "50G" || rate == "50GbE" || rate == "100G" || rate == "100GbE") {
        return LANE_RATE_EDR_CAP;
    }
    if (rate == "IB-HDR" || rate == "HDR" || rate == "200G" || rate == "200GbE" || rate == "400G" || rate == "400GbE") {
        return LANE_RATE_HDR_CAP;
    }
    if (rate == "1G" || rate == "1GbE") {
        return LANE_RATE_1G_CAP;
    }
    if (rate == "XAUI" || rate == "2.5G" || rate == "2.5GbE") {
        return LANE_RATE_XAUI_CAP;
    }
    if (rate == "50GE-KR4" || rate == "12.89G" || rate == "12.89GbE") {
        return LANE_RATE_50G_CAP;
    }
    return LANE_RATE_EDR_CAP;
}

u_int32_t prbsMaskToRateNum(u_int32_t mask)
{
    if (mask == PRBS_SDR) {
        return 1;
    }
    if (mask == PRBS_DDR) {
        return 5;
    }
    if (mask == PRBS_QDR) {
        return 10;
    }
    if (mask == PRBS_FDR10) {
        return 40;
    }
    if (mask == PRBS_FDR) {
        return 56;
    }
    if (mask == PRBS_EDR) {
        return 100;
    }
    if (mask == PRBS_HDR) {
        return 200;
    }
    if (mask == PRBS_1G) {
        return 1;
    }
    if (mask == PRBS_XAUI) {
        return 2;
    }
    if (mask == PRBS_50G) {
        return 12;
    }
    return 0;
}

bool prbsLaneRateCheck(const string &rate)
{
    if (rate == "SDR" || rate == "IB-SDR") {
        return true;
    }
    if (rate == "DDR" || rate == "IB-DDR" || rate == "5G") {
        return true;
    }
    if (rate == "QDR" || rate == "IB-QDR") {
        return true;
    }
    if (rate == "FDR10" || rate == "IB-FDR10" || rate == "10G" || rate == "40G") {
        return true;
    }
    if (rate == "FDR" || rate == "IB-FDR" || rate == "14G") {
        return true;
    }
    if (rate == "EDR" || rate == "IB-EDR" || rate == "25G" || rate == "50G" || rate == "100G") {
        return true;
    }
    if (rate == "HDR" || rate == "IB-HDR" || rate == "200G") {
        return true;
    }
    if (rate == "1G") {
        return true;
    }
    if (rate == "XAUI" || rate == "2.5G") {
        return true;
    }
    if (rate == "50GE-KR4" || rate == "12.89G") {
        return true;
    }
    if (rate == "") {
        return true;
    }
    return false;
}

string prbsMaskToTuningStatus(u_int32_t mask)
{
    if (mask == PRBS_TUNING_NOT_PERFORMED) {
        return "PRBS mode tuning was not performed.";
    }
    if (mask == PRBS_TUNING_PERFORMING) {
        return "Performing PRBS mode tuning.";
    }
    if (mask == PRBS_TUNING_COMPLETE) {
        return "PRBS mode tuning completed.";
    }
    return "N/A";
}

string prbsMaskToLockStatus(u_int32_t mask, u_int32_t numOfLanesToUse)
{
    string res = "";
    for (u_int32_t i = 0; i < numOfLanesToUse; i++) {
        if (mask & 1 << i) {
            res += "Locked";
        } else {
            res += "Not Locked";
        }
        if (i < numOfLanesToUse - 1) {
            res += ",    ";
        }
    }
    return res;
}

bool checkPrbsCmd(const string &prbsCmd)
{
    if (prbsCmd != "DS" && prbsCmd != "EN" && prbsCmd != "TU") {
        return false;
    }
    return true;
}

bool checkTestMode(const string &testMode)
{
    if (testMode != "Nominal" && testMode != "NOMINAL" && testMode != "CORNER"
        && testMode != "DRIFT" && testMode != "") {
        return false;
    }
    return true;
}

string FEC2Str100G(u_int32_t mask)
{
    string maskStr = "";
    if (mask & NO_FEC) {
        maskStr += "No-FEC,";
    }
    if (mask & RS_FEC) {
        maskStr += "RS-FEC(528,514),";
    }

    return deleteLastComma(maskStr);
}

string FEC2Str50G25G(u_int32_t mask)
{
    string maskStr = "";
    if (mask & NO_FEC) {
        maskStr += "No-FEC,";
    }
    if (mask & FC_FEC) {
        maskStr += "FireCode FEC,";
    }
    if (mask & RS_FEC) {
        maskStr += "RS-FEC(528,514),";
    }

    return deleteLastComma(maskStr);
}

string FEC2Str(const string &fecShort)
{
    string fec = "";
    if (fecShort == "NF") {
        fec = "No FEC";
    } else if (fecShort == "FC") {
        fec = "Firecode FEC";
    } else if (fecShort == "RS") {
        fec = "RS FEC";
    }
    return fec;
}

string FECReq2Str(u_int32_t mask, bool linkUP)
{
    string maskStr = "";
    if (!linkUP) {
        return "N/A";
    }
    if (mask & FEC_REQUSET_NF) {
        maskStr += "No-FEC,";
    }
    if (mask & FEC_REQUSET_FC) {
        maskStr += "Firecode FEC,";
    }
    if (mask & FEC_REQUSET_RS528) {
        maskStr += "Standard RS-FEC - RS(528,514),";
    }
    if (mask & FEC_REQUSET_RS271) {
        maskStr += "Standard LL RS-FEC - RS(271,257),";
    }
    if (mask & FEC_REQUSET_RS277) {
        maskStr += "Mellanox Strong RS-FEC - RS(277,257),";
    }
    if (mask & FEC_REQUSET_RS163) {
        maskStr += "Mellanox LL RS-FEC - RS(163,155),";
    }
    if (mask & FEC_REQUSET_ZLF) {
        maskStr += "Zero Latency FEC (ZLF),";
    }

    if (maskStr == "") {
        maskStr = "N/A,";
    }
    return deleteLastComma(maskStr);
}

int fecToBit(const string &fec)
{
    if (fec == "AU") {
        return 0;
    }
    if (fec == "NF") {
        return 1;
    }
    if (fec == "FC") {
        return 2;
    }
    if (fec == "RS") {
        return 4;
    }
    return 0;
}

string speedToStr(const string &speed)
{
    if (speed == "200GbE" || speed == "IB-HDR") {
        return "200g";
    }
    if (speed == "100GbE" || speed == "IB-EDR") {
        return "100g";
    }
    if (speed == "50GbE") {
        return "50g";
    }
    if (speed == "25GbE") {
        return "25g";
    }
    if (speed == "40GbE" || speed == "IB-FDR10") {
        return "10g_40g";
    }
    if (speed == "10GbE" || speed == "IB-QDR") {
        return "10g_40g";
    }
    if (speed == "IB-FDR") {
        return "56g";
    }
    return "100g";
}

PAOS_CMD paos_to_int(const string &cmd)
{
    if (cmd == "UP") {
        return UP;
    }
    if (cmd == "DN") {
        return DN;
    }
    if (cmd == "TG") {
        return TG;
    }
    return NO;
}

int pepc_force_mode_to_int(const string &forceMode)
{
    if (forceMode == "MA") {
        return 0;
    }
    if (forceMode == "SL") {
        return 1;
    }
    return 0;
}

int pepc_an_mode_to_int(const string &anMode)
{
    if (anMode == "AU") {
        return 0;
    }
    if (anMode == "MA") {
        return 1;
    }
    if (anMode == "SL") {
        return 2;
    }
    return 0;
}

bool endsWith(std::string const & value, std::string const & ending)
{
    if (ending.size() >= value.size()) {
        return false;
    }
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

void findAndReplace(string& source, string const& find, string const& replace)
{
    for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;) {
        source.replace(i, find.length(), replace);
        i += replace.length();
    }
}

string getCableIdentifier(u_int32_t identifier)
{
    string identifierStr;
    switch (identifier) {
    case IDENTIFIER_QSFP28:
        identifierStr = "QSFP28";
        break;

    case IDENTIFIER_QSFP_PLUS:
        identifierStr = "QSFP+";
        break;

    case IDENTIFIER_SFP:
        identifierStr = "SFP28/SFP+";
        break;

    case IDENTIFIER_QSA:
        identifierStr = "QSA (QSFP->SFP)";
        break;

    case IDENTIFIER_BACKPLANE:
        identifierStr = "Backplane";
        break;

    default:
        identifierStr = "N/A";
    }
    return identifierStr;
}

bool getQsfp(u_int32_t identifier)
{
    return (identifier == 0 || identifier == 1);
}

string getCableType(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType) {
    case UNIDENTIFIED:
        cableTypeStr = "Unidentified";
        break;

    case ACTIVE:
        cableTypeStr = "Active cable (active copper / optics)";
        break;

    case OPTICAL_MODULE:
        cableTypeStr = "Optical Module (separated)";
        break;

    case PASSIVE:
        cableTypeStr = "Passive copper cable";
        break;

    case UNPLUGGED:
        cableTypeStr = "Cable unplugged";
        break;

    default:
        cableTypeStr = "Unidentified";
        break;
    }
    return cableTypeStr;
}

string getPowerClass(u_int32_t powerClass)
{
    string powerClassStr;
    switch (powerClass) {
    case POWER_CLASS1:
        powerClassStr = "1.0 W max";
        break;

    case POWER_CLASS2:
        powerClassStr = "1.5 W max";
        break;

    case POWER_CLASS3:
        powerClassStr = "2.0 W max";
        break;

    case POWER_CLASS4:
        powerClassStr = "2.5 W max";
        break;

    case POWER_CLASS5:
        powerClassStr = "3.5 W max";
        break;

    case POWER_CLASS6:
        powerClassStr = "4.0 W max";
        break;

    case POWER_CLASS7:
        powerClassStr = "4.5 W max";
        break;

    case POWER_CLASS8:
        powerClassStr = "5.0 W max";
        break;

    default:
        powerClassStr = "N/A";
    }
    return powerClassStr;
}

string getTemp(u_int32_t temp)
{
    if (temp & 0x8000) {
        return "-" + to_string(((~temp & 0xFFFF) + 1) / 256);
    }
    return to_string(temp / 256);
}

float getPower(u_int16_t power)
{
    if (power & 0x8000) {
        return -((~power & 0xFFFF) + 1);
    }
    return power;
}

int getHeight(u_int16_t height)
{
    if (height & 0x8000) {
        return -((~height & 0xFFFF) + 1);
    }
    return height;
}

int getPhase(u_int8_t phase)
{
    if (phase & 0x80) {
        return -((~phase & 0xFF) + 1);
    }
    return phase;
}

int getVersion(u_int8_t version)
{
    if (version & 0x8) {
        return -((~version & 0xF) + 1);
    }
    return version;
}

string getGroupStr(u_int32_t advancedOpcode)
{
    if (advancedOpcode == 0 || advancedOpcode == 1023) {
        return "N/A";
    } else if (advancedOpcode < 1023) {
        return "PHY FW";
    } else if (advancedOpcode < 2048) {
        return "MNG FW";
    }
    return "CORE/DRIVER";
}

string toUpperCase(string &str)
{
    for (u_int32_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

string getCableMedia(u_int32_t cableType)
{
    string cableTypeStr;
    switch (cableType) {
    case UNIDENTIFIED:
        cableTypeStr = "Unidentified";
        break;

    case ACTIVE:
        cableTypeStr = "Active";
        break;

    case OPTICAL_MODULE:
        cableTypeStr = "Optical Module";
        break;

    case PASSIVE:
        cableTypeStr = "Passive";
        break;

    case UNPLUGGED:
        cableTypeStr = "Unplugged";
        break;

    default:
        cableTypeStr = "Unidentified";
    }
    return cableTypeStr;
}

string pcieSpeedStr(u_int32_t linkSpeedActive)
{
    string linkSpeedActiveStr;
    if (linkSpeedActive & GEN4) {
        linkSpeedActiveStr = "16G-Gen 4";
    } else if (linkSpeedActive & GEN3) {
        linkSpeedActiveStr = "8G-Gen 3";
    } else if (linkSpeedActive & GEN2) {
        linkSpeedActiveStr = "5G-Gen 2";
    } else if (linkSpeedActive & GEN1) {
        linkSpeedActiveStr = "2.5G-Gen 1";
    } else {
        linkSpeedActiveStr = "N/A";
    }
    return linkSpeedActiveStr;
}

string pcieDeviceStatusStr(u_int32_t deviceStatus)
{
    string deviceStatusStr, comma;
    if ((deviceStatus >> 0) & 0x1){
        deviceStatusStr += "Correctable Error detected";
        comma=", ";
    }
    if ((deviceStatus >> 1) & 0x1){
        deviceStatusStr += comma + "Non-Fatal Error detected";
        comma=", ";
    }
    if ((deviceStatus >> 2) & 0x1){
        deviceStatusStr  += comma + "Fatal Error detected" + comma;
        comma=", ";
    }
    if ((deviceStatus >> 3) & 0x1){
        deviceStatusStr += comma + "Unsupported Request detected";
        comma=", ";
    }
    if ((deviceStatus >> 4) & 0x1){
        deviceStatusStr += comma + "AUX power";
        comma=", ";
    }
    if ((deviceStatus >> 5) & 0x1){
        deviceStatusStr += comma + "Transaction Pending";
    }
    if ("" != deviceStatusStr){
        deviceStatusStr += ".";
    }
    return deviceStatusStr;
}
