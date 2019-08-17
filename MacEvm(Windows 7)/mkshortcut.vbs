Option Explicit
Dim obj, nLink, strDesktop, Directory

Set obj = CreateObject("wscript.shell")

strDesktop = obj.SpecialFolders("Desktop")

Set nLink = obj.CreateShortcut(strDesktop + "\Admin.lnk")

dim fso: set fso = CreateObject("Scripting.FileSystemObject")

dim CurrentDirectory
    CurrentDirectory = fso.GetAbsolutePathName(".")




nLink.TargetPath = CurrentDirectory + "\Admin.exe"
nLink.Description = "Admin of MacEvm."
nLink.IconLocation = CurrentDirectory + "\Admin.ico"
nLink.WorkingDirectory = CurrentDirectory
nLink.Save