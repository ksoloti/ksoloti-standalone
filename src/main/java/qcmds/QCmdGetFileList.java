/**
 * Copyright (C) 2013, 2014 Johannes Taelman
 * Edited 2023 - 2024 by Ksoloti
 *
 * This file is part of Axoloti.
 *
 * Axoloti is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * Axoloti is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Axoloti. If not, see <http://www.gnu.org/licenses/>.
 */
package qcmds;

import axoloti.Connection;

/**
 *
 * @author Johannes Taelman
 */
public class QCmdGetFileList implements QCmdSerialTask {

    boolean done = true;

    @Override
    public String GetStartMessage() {
        return "Receiving SD card file list...";
    }

    @Override
    public String GetDoneMessage() {
        if (done) {
            return "Done receiving SD card file list.\n";
        } else {
            return "Incomplete SD card file list.\n";
        }
    }

    @Override
    public QCmd Do(Connection connection) {
        connection.ClearSync();
        connection.ClearReadSync();
        connection.TransmitGetFileList();
        int timeout = 0;
        while (!connection.WaitReadSync()) {
            timeout++;
            if (timeout > 20) {
                done = false;
                break;
            }
        }
        return this;
    }
}
