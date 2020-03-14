//##########################################################################
//#                                                                        #
//#                      CLOUDCOMPARE PLUGIN: qCHAIKIN                     #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 or later of the License.      #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                         COPYRIGHT: CNRS / OSUR                         #
//#                                                                        #
//##########################################################################

#ifndef CHAIKIN_PLUGIN_COMMANDS_HEADER
#define CHAIKIN_PLUGIN_COMMANDS_HEADER

//CloudCompare
#include "ccCommandLineInterface.h"

//Local
//#include "qCHAIKINProcess.h"

static const char COMMAND_CHAIKIN[] = "CHAIKIN";

struct CommandCHAIKIN : public ccCommandLineInterface::Command
{
	CommandCHAIKIN() : ccCommandLineInterface::Command("CHAIKIN smoothing algorithm", COMMAND_CHAIKIN) {}

	virtual bool process(ccCommandLineInterface& cmd) override
	{
		cmd.print("[CHAIKIN]");
		if (cmd.arguments().empty())
		{
			return cmd.error(QString("Missing parameter: number of iterations after \"-%1\"").arg(COMMAND_CHAIKIN));
		}

		//open specified file
		bool ok = false;
		int iterationsCount = cmd.arguments().takeFirst().toInt(&ok);
		if(!ok)
		{
			cmd.error(QString("Invalid parameter: number of iterations expected after \"-%1\"").arg(COMMAND_CHAIKIN));
			return;
		}

		//QString paramFilename(cmd.arguments().takeFirst());
		//cmd.print(QString("Parameters file: '%1'").arg(paramFilename));

		if (cmd.clouds().size() != 1)
		{
			cmd.error("only one cloud expected)");
			return false;
		}

		ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(cmd.clouds()[0.front().pc);

		//display dialog
		qCHAIKINDialog dlg(cloud1, cloud2, nullptr);
		if (!dlg.loadParamsFromFile(paramFilename))
		{
			return false;
		}
		dlg.setCorePointsCloud(corePointsCloud);

		QString errorMessage;
		ccPointCloud* outputCloud = nullptr; //only necessary for the command line version in fact
		if (!qCHAIKINProcess::Compute(dlg, errorMessage, outputCloud, !cmd.silentMode(), cmd.widgetParent()))
		{
			return cmd.error(errorMessage);
		}

		if (outputCloud)
		{
			CLCloudDesc cloudDesc(outputCloud, cmd.clouds()[0].basename + QObject::tr("_CHAIKIN"), cmd.clouds()[0].path);
			if (cmd.autoSaveMode())
			{
				QString errorStr = cmd.exportEntity(cloudDesc, QString(), 0, false, true);
				if (!errorStr.isEmpty())
				{
					cmd.error(errorStr);
				}
			}
			//add cloud to the current pool
			cmd.clouds().push_back(cloudDesc);
		}

		return true;
	}
};

#endif //CHAIKIN_PLUGIN_COMMANDS_HEADER
