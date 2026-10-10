# Captures the game window's client area (tools/re/opprobe.py shot)
param([string]$Out = "proto.png", [string]$Process = "prototypef")
Add-Type -AssemblyName System.Drawing
Add-Type @"
using System;
using System.Runtime.InteropServices;
public static class Win {
	[StructLayout(LayoutKind.Sequential)] public struct RECT { public int Left, Top, Right, Bottom; }
	[DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT rect);
	[DllImport("user32.dll")] public static extern bool GetClientRect(IntPtr hWnd, out RECT rect);
	[DllImport("user32.dll")] public static extern bool ClientToScreen(IntPtr hWnd, ref POINT point);
	[StructLayout(LayoutKind.Sequential)] public struct POINT { public int X, Y; }
	[DllImport("user32.dll")] public static extern bool IsIconic(IntPtr hWnd);
	[DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
}
"@
[Win]::SetProcessDPIAware() | Out-Null
$p = Get-Process $Process -ErrorAction Stop | Select-Object -First 1
$h = $p.MainWindowHandle
# The proxy d3d9.dll runs the game in a window: capture its client area (it must not be covered by other windows)
$client = New-Object Win+RECT
[Win]::GetClientRect($h, [ref]$client) | Out-Null
$origin = New-Object Win+POINT
[Win]::ClientToScreen($h, [ref]$origin) | Out-Null
$w = $client.Right - $client.Left
$hgt = $client.Bottom - $client.Top
"window $w x $hgt at $($origin.X),$($origin.Y), minimized: $([Win]::IsIconic($h))"
$bmp = New-Object System.Drawing.Bitmap $w, $hgt
$g = [System.Drawing.Graphics]::FromImage($bmp)
$g.CopyFromScreen($origin.X, $origin.Y, 0, 0, $bmp.Size)
$bmp.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
"saved $Out"
