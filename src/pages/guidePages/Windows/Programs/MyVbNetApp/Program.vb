Imports System
Imports System.Diagnostics
Imports System.IO
Imports System.Threading

Module Program
    Sub Main(args As String())
        ' Запуск mpv с указанным файлом
        Dim process As New Process()
        process.StartInfo.FileName = "mpv"
        process.StartInfo.Arguments = "D:\Privat\Content\content_15.webm"
        process.StartInfo.UseShellExecute = False
        process.StartInfo.RedirectStandardInput = True
        process.Start()
        process.WaitForExit()
    End Sub
End Module