python flash.py --source-image ..\ccs_workspace\allhallowtide_badge\Debug\allhallowtide_badge.txt -i %1
msp430flasher -v -w tmp.txt -z [VCC,RESET]