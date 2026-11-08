// pure3d::DisplaySettings (the display's settings, 0x138 bytes): shared by the render context's startup settings and
// engine::Display, which starts with them.
#ifndef PURE3D_DISPLAYSETTINGS_H
#define PURE3D_DISPLAYSETTINGS_H

namespace pure3d
{
	// The settings of the display (0x138 bytes): the window it is created on first, the size, the depth of the colour,
	// the gamma and a few modes. engine::Display (0x10617A30) starts with them.
	struct DisplaySettings
	{
		// 0x106179B0
		DisplaySettings();

		void* window;
		int width;
		int unknown8;
		int unknownC;
		float unknown10;
		int unknown14;
		int unknown18;
		int unknown1C;
		// 0x20: 1 when the display is windowed
		int unknown20;
		bool unknown24;
		int unknown28;
		// 0x2C: whether the device waits for the vertical blank
		bool unknown2C;
		bool unknown2D;
		bool unknown2E;
		bool unknown2F;
		// 0x30: a table of 0x100 bytes whose last word points back at the table
		struct Unknown30
		{
			Unknown30()
			{
				unknown100 = this;
			}
			~Unknown30()
			{
				unknown100 = this;
			}

			unsigned char unknown0[0x100];
			Unknown30* unknown100;
		};
		Unknown30 unknown30;
		int unknown134;
	};
}

#endif
