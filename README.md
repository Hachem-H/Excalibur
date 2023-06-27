# Excalibur
_*Note*: This repository is still a work in progress._

Excalibur, an insidious piece of software, poses a grave threat to computer systems. Disguised as a seemingly innocent game, it cunningly infiltrates through an installer that, like other installers, demands administrative privileges for execution. While the installation process appears to proceed normally, unbeknownst to the user, Excalibur clandestinely carries out a malicious operation in the background. Behind the façade of harmless installation, Excalibur deploys a sinister tactic that targets the Master Boot Record (`MBR`) of the computer's storage system. The `MBR`, a vital component responsible for booting the operating system, becomes the victim of Excalibur's destructive intentions. Through a series of covert actions, Excalibur overwrites the `MBR`, irreversibly tampering with its critical data structures. The consequences of this covert attack are severe. Once the `MBR` is compromised, the operating system becomes completely inoperable, rendering the computer unusable. The insidious nature of Excalibur lies in its ability to silently execute this damaging process, leaving users unaware of the impending catastrophe until it is too late. If the installer overwrites the Master Boot Record (`MBR`), it is conceivable to develop a custom solution that allows users to create and write their own `MBR`. This enhanced functionality provides an opportunity for users to exercise greater control over their system's boot process and potentially load alternative operating systems or customized configurations.

## OpenGL Support for Legacy and Virtual Machines
To enable older machines and virtual machines without a modern OpenGL version, you can copy the `opengl32.dll` file from the`Vendor/` folder and paste it into the installation directory (usually located at `C:\Program Files\Excalibur`). By doing so, you ensure that the required `opengl32.dll` file is present in the installation directory, enabling the application to function correctly on these machines.

*_The `opengl32.dll` is provided by Mesa3D_ 

## Disclaimer

This code is shared strictly for educational purposes only. It was developed to demonstrate potential security vulnerabilities and should not be used for any malicious or harmful activities.

By accessing and using this code, you acknowledge that:

1. The code is provided "as is," and the author(s) make no warranties or guarantees regarding its functionality, security, or fitness for any purpose.
2. The code may contain vulnerabilities or errors that could lead to unintended consequences or harm to computer systems or networks.
3. You will not use this code for any unauthorized or malicious activities, including but not limited to spreading malware, gaining unauthorized access, or causing disruption to computer systems or networks.
4. The author(s) of this code will not be held liable for any damages or losses resulting from the use or misuse of this code.

Please use this code responsibly and only for educational purposes. If you discover any vulnerabilities or improvements, kindly report them to the author(s) to help enhance its educational value.

By using this code, you agree to these terms and conditions.
