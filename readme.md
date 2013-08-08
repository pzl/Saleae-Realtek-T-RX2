T/RX2 Logic Analyzer
================

This plugin is for use in the [Saleae Logic](http://www.saleae.com/downloads) program to decode captured data from Realtek's TX2/RX2 chip pair, used in RC cars.

Installation
-----
To build the plugin, change to the plugin directory and run `python build_analyzer.py`. The `build_analyzer` file has been [modified]() from the provided build script from Saleae to accommodate an error building on 64-bit OS X. This plugin should build cross-platform, depending on python version.

Once built (look for any errors in the build output), open Saleae Logic and Click

Options > Preferences > "Developer" Tab

The only option should be an area to specify a folder. Point this to the `release` folder in this plugin directory. If you already have a generic user-directory to collect plugins, copy `release/libTRX2Analyzer.dylib` to your folder. Other architectures may use other file extensions (Mac: dylib; Linux: so; Windows: dll).


Use
-----
After capturing data from The TX2's SO pin, or the receiving circuit / input on the RX2 (or simulating data), add the analyzer "Realtek T/RX2" and specify the channel used to capture this data. Also specify whether or not you are capturing transmitted or received data (TX2 or RX2 respectively). 

The plugin will then place a green "start" marker at the start of every header. A data bubble is placed above the command portion of the packet with the command number sent.

![analyzer](http://pzl.github.io/Saleae-Realtek-T-RX2/TRX2-analyzer.png)

As-is
------

This software is not yet robust against packet errors, artifacts from button bouncing, different clock rates and more. It is, at best, beta-quality. It is provided as-is, with no guarantee of it's accuracy.