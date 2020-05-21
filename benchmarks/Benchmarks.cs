//----------------------------------------------------------------
//BENCHMARKS PROGRAM.CS
//
//compile:
//dotnet publish -f netcoreapp2.0 -c Release -r rhel.7-x64 --self-contained yes
//
//stores exectuable in:
//current_directory/bin/Release/netcoreapp2.0/rhel.7-x64/publish
//
//execute with:
// ./CMD /home/nrbiddle/MetaMorpheus-0.0.295/CMD/test_toml_2.toml 20000 /home/nrbiddle/MetaMorpheus-0.0.295/CMD/sliced-raw.mzML /home/nrbiddle/MetaMorpheus-0.0.295/CMD/test_write_mzml2.mzML
//----------------------------------------------------------------


using FlashLFQ;
using MassSpectrometry;
using MzLibUtil;
using EngineLayer;
using Fclp;
using Nett;
using Proteomics;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using TaskLayer;
using IO.MzML;

using System.Diagnostics;

namespace MetaMorpheusCommandLine
{
    internal static class Program
    {

        private static void Main(string[] args)
        {
            Console.WriteLine("Welcome to MetaMorpheus");


            // EDGAR: Createing the FlashLfqEngine is unforunately required,
            // otherwise the code just crashes when executed.

            SpectraFileInfo mzml = new SpectraFileInfo("sliced-mzml.mzml", "a", 0, 1, 0);
            var pg = new FlashLFQ.ProteinGroup("MyProtein", "gene", "org");
            Identification id3 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR",
                                                    1350.65681, 94.12193, 2, new List<FlashLFQ.ProteinGroup> { pg });
            Identification id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR",
                                                    1350.65681, 94.05811, 2, new List<FlashLFQ.ProteinGroup> { pg });
            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id3, id4 }, normalize: true);
            // EDGAR: End of part required to avoid crash
            
            
            //generate toml
            Console.WriteLine("generating toml with {0} key-value pairs", args[1]);
            var tomlData = Toml.Create();
            for (int i = 0; i < int.Parse(args[1]); i++){
                tomlData.Add(i.ToString(), i);
            }

            //write toml
            Console.WriteLine("writing toml file {0}", args[0]);
            Stopwatch stopwatch = Stopwatch.StartNew();
            Toml.WriteFile(tomlData, args[0]);
            stopwatch.Stop();
            Console.WriteLine("Time elapsed for toml write: {0}\n", stopwatch.ElapsedMilliseconds);


            //read file
            Console.WriteLine("reading toml file {0}", args[0]);
            stopwatch = Stopwatch.StartNew();
            var tomlRead = Toml.ReadFile(args[0]);
            stopwatch.Stop();
            Console.WriteLine("Time elapsed for toml read: {0}\n", stopwatch.ElapsedMilliseconds);


            //read mzml file
            Console.WriteLine("reading mzml file {0}", args[2]);
            stopwatch = Stopwatch.StartNew();
            var msData = Mzml.LoadAllStaticData(args[2]);
            stopwatch.Stop();
            Console.WriteLine("Time elapsed for mzML read: {0}\n", stopwatch.ElapsedMilliseconds);


            //write mzml file
            Console.WriteLine("writing mzml file {0}", args[3]);
            stopwatch = Stopwatch.StartNew();
            MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(msData, args[3], false);
            stopwatch.Stop();
            Console.WriteLine("Time elapsed for mzML write: {0}", stopwatch.ElapsedMilliseconds);
        }
    }
}
