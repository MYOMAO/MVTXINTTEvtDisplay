#Commands to Produce the Plots: #

Get the codes by git clone https://github.com/MYOMAO/MVTXINTTEvtDisplay.git

Build the code by source Build.sh for cshell and source BuildBshell.sh for bash shell

Set the detector type to run at https://github.com/MYOMAO/MVTXINTTEvtDisplay/blob/master/macros/common/G4_Input.C#L48

DetectorType = 0 is MVTX

DetectorType = 1 is INTT

Default is MVTX (DetectorType = 0): https://github.com/MYOMAO/MVTXINTTEvtDisplay/blob/master/macros/common/G4_Input.C#L48

Define the Filelist to run. MVTX: FileList.txt and INTT: INTTFileList.txt

Default MVTX Filelist: https://github.com/MYOMAO/MVTXINTTEvtDisplay/blob/master/macros/detectors/sPHENIX/FileList.txt

Default INTT Filelist: https://github.com/MYOMAO/MVTXINTTEvtDisplay/blob/master/macros/detectors/sPHENIX/INTTFileList.txt

Output file stored at OutFile/MVTX and OutFile/INTT 


#To Run the Codes: #

source Build.sh

cd macros/detectors/sPHENIX

mkdir OutFile/MVTX

mkdir OutFile/INTT

root -b -l -q Fun4All_G4_sPHENIX.C'(1)'

Then we can merge the MVTX and INTT output files. For MVTX


cd OutFile/MVTX/

hadd MVTXAll.root *.root

root -l MVTXAll.root




