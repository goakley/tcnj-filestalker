This file is part of FileStalker.

FileStalker is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

FileStalker is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with FileStalker.  If not, see <http://www.gnu.org/licenses/>.

---

To use FileStalker as a standalone, run it with a single argument, 
which is the path to the directory that should be monitored.
Remember to pipe the output to a log file, and fork/screen the program.

./FileStalker "/path/to/directory" > log.file &

You can run the UI at any time in order to view the output of the log
in a formatted way.

./FileStalkerUI

---

To install file stalker, run 'make install' as root.
Run the program manually as follows:
filestalker &

The UI can be run with:
filestalkerui
