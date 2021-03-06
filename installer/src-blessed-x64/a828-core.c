/*********************************************************************************

AVerMedia TECHNOLOGIES, Inc.
AVerMedia Linux Driver License Agreement

 

IMPORTANT: This AVerMeida Linux Driver is supplied to you by
AVerMedia TECHNOLOGIES, Inc. ("AVerMedia") in consideration 
of your agreement to the following terms, and your use, installation, 
modification or redistribution of this AVerMedia Linux Driver 
constitutes acceptance of these terms. If you do not agree with 
these terms, please do not use, install, modify or redistribute 
this AVerMedia Linux Driver.

1. License. Any driver sources, binaries, utilities, documentation 
and other materials accompanying this License, whether on disk, 
print or electronic documentation, in read only memory, or any 
other media, (collectively, the "AVerMedia Linux Driver") are 
licensed, not sold, to you by AVerMedia for use only under the terms
of this License, and AVerMedia reserves all rights not expressly
granted to you. The rights granted herein are limited to AVerMedia's
intellectual property rights in the AVerMedia Linux Driver and do not
include any other patents or intellectual property rights. You own
the media on which the AVerMedia Linux Driver is recorded but AVerMedia
retains ownership of the AVerMedia Linux Driver itself and its
derivative works. The AVerMedia Linux Driver in this package and
any copies, modifications and derivative works which this License
authorizes you to make are subject to this License. The binaries
part of AVerMedia Linux Driver is ported from Windows driver and
is under some other NDA, so the original source code will not be
released.

2. Permitted Uses and Restrictions. You may use, copy, redistribute
or install the original AVerMedia Linux Driver to test or demonstrate
the AVerMedia Linux Driver with AVerMedia's products. You may also
modify the released source code in order to improve the compatibilities,
operability and functionalities with AVerMedia's products as long as
this License in whole are remained and subsequently use, copy,
redistribute or install the derivative works. You have no right to
reverse engineer, decompile, disassemble the accompanying object files
through the released source code, nor to modify, incorporate into or
compile in combination with your own programs to operate with any
product other than from AVerMedia. Your rights under this License
will terminate automatically without notice from AVerMedia if you
fail to comply with any term(s) of this License.

3. Disclaimer of Warranty. The AVerMedia Linux Driver may be "alpha",
"beta", "development", pre-release, untested, and/or not fully tested
and may contain errors that could cause failures or loss of data, be
incomplete or contain inaccuracies. YOU EXPRESSLY ACKNOWLEDGE AND AGREE
THAT USE OF THE AVERMEDIA LINUX DRIVER IS AT YOUR SOLE RISK AND THAT THE
ENTIRE RISK AS TO SATISFACTORY QUALITY, PERFORMANCE, ACCURACY AND EFFORT
IS WITH YOU. THE AVERMEDIA LINUX DRIVER IS PROVIDED "AS IS" WITH ALL
FAULTS. THE USER ASSUMES TOTAL RESPONSIBILITY AND ALL RISKS ASSOCIATED
WITH USE OF THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, RISKS OF ANY
DEFECTS, INACCURACIES, PROGRAM ERRORS, DAMAGE TO OR LOSS OF DATA,
PROGRAMS OR EQUIPMENT, UNAVAILABILITY OR INTERRUPTION OF OPERATIONS.
AVERMEDIA DOES NOT MAKE, AND EXPRESSLY DISCLAIM, ANY EXPRESS OR IMPLIED
WARRANTIES OF ANY KIND WHATSOEVER, INCLUDING, WITHOUT LIMITATION,
ANY WARRANTIES OR FITNESS FOR A PARTICULAR PURPOSE, AND ANY WARRANTIES
OF TITLE OR NON-INFRINGEMENT. AVERMEDIA DOES NOT WARRANT THAT THE USE
OR OPERATION OF THE SOFTWARE WILL BE UNITERRUPTED OR ERROR FREE.

4. Complete Agreement. This License constitutes the entire agreement
between the parties with respect to the use of the AVerMedia Linux
Driver licensed hereunder and supersedes all prior or contemporaneous
understandings regarding such subject matter. No amendment to or
modification of this License will be binding unless in writing and
signed by AVerMedia. Any translation of this License is done for
local requirements and in the event of a dispute between the English
and any non-English versions, the English version of this License
shall govern.

*********************************************************************************/
#include	<linux/usb.h>
#include	<linux/types.h>

#include	"KernToCUsb.hpp"
#include	"aver_version.h"
#include	"aver/id.h"
#include	"a828-core.h"
#include	<linux/version.h>
#include	<linux/module.h>

MODULE_DESCRIPTION("AVerMedia USB Hybrid+FM Volar driver v"DRIVER_VER);
MODULE_AUTHOR("MPD Linux Team");
MODULE_LICENSE("AVerMedia TECHNOLOGIES, Inc.");



int AlwaysPowerOn=0;
module_param(AlwaysPowerOn, bool, 0644);
MODULE_PARM_DESC(AlwaysPowerOn, " If set 'AlwaysPowerOn=1', the device does not turn off the power. Default value is 0.");



int PowerOffDelay=30;
module_param(PowerOffDelay, int, 0644);
MODULE_PARM_DESC(PowerOffDelay, "Set the idle time in seconds, after which device is power down. Default value is 30");





int DefaultSharpness=50;
module_param(DefaultSharpness, int, 0644);
MODULE_PARM_DESC(DefaultSharpness, "Set default video sharpness. Range 0~100. Default value is 50.");

int DefaultBrightness=127;
module_param(DefaultBrightness, int, 0644);
MODULE_PARM_DESC(DefaultBrightness, "Set default video brightness. Range 0~255. Default value is 127.");

int DefaultContrast=127;
module_param(DefaultContrast, int, 0644);
MODULE_PARM_DESC(DefaultContrast, "Set default video contrast. Range 0~255. Default value is 127.");

int DefaultSaturation=104;
module_param(DefaultSaturation, int, 0644);
MODULE_PARM_DESC(DefaultSaturation, "Set default video saturation. Range 0~255. Default value is 104.");

int DefaultHue=127;
module_param(DefaultHue, int, 0644);
MODULE_PARM_DESC(DefaultHue, "Set default video hue. Range 0~255. Default value is 127.");





static struct usb_device_id usb_table [] = {
	{ USB_DEVICE(USB_VID_AVer, USB_PID_A828) },
	{ USB_DEVICE(USB_VID_AVer, USB_PID_A301) },
	{ }					
};
MODULE_DEVICE_TABLE (usb, usb_table);





static int usb_probe
(struct usb_interface *interface, const struct usb_device_id *id)
{
	return UsbProbe((pUsb_interface)interface);
}

static void usb_disconnect(struct usb_interface *interface)
{
	UsbDisconnect((pUsb_interface)interface);
}

static struct usb_driver my_driver = {
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,16) 	&& !(defined(USB_FC5_HACK) && USB_FC5_HACK)
	.owner =	THIS_MODULE,
#endif

	.name =		A828_DRIVER_NAME,
	.probe =	usb_probe,
	.disconnect =	usb_disconnect,
	.id_table =	usb_table,
};

static int __init mod_init(void)
{
	printk(KERN_INFO "nin(%s:%d):: init\n", __func__, __LINE__);
	return UsbModInit((pUsb_driver)&my_driver);
}

static void __exit mod_exit(void)
{
	UsbModExit();
}

module_init (mod_init);
module_exit (mod_exit);
