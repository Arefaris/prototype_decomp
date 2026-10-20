// The instances of GPtr and GRefCountBase that the engine has as functions of their own (the unit of the library around
// 0x1095A510; file name guessed). The pointer helpers exist once per class of object in the engine; the ones kept here are
// those of GFile and GImage.
#include "code/gfx/gfile.h"
#include "code/gfx/gimage.h"

// FUNCTION: ENGINE 0x1095A560 ; GPtr<class GFile>::ReleaseObject
// FUNCTION: ENGINE 0x1095A590 ; GPtr<class GImage>::ReleaseObject
// FUNCTION: ENGINE 0x1095A580 ; GPtr<class GFile>::SetRaw
// FUNCTION: ENGINE 0x1095A5B0 ; GPtr<class GFile>::GetPtr
// FUNCTION: ENGINE 0x1095A5C0 ; GPtr<class GImage>::GetPtr
// FUNCTION: ENGINE 0x1095BDD0 ; GPtr<class GRefCountBaseImpl>::GetPtr
// FUNCTION: ENGINE 0x1095BD70 ; GPtr<class GFile>::operator=
// FUNCTION: ENGINE 0x1095BDA0 ; GPtr<class GFile>::SetCounted
void (GPtr<GFile>::*gKeepFilePtr[])() = {&GPtr<GFile>::ReleaseObject};
void (GPtr<GImage>::*gKeepImagePtr[])() = {&GPtr<GImage>::ReleaseObject};
GPtr<GFile>& (GPtr<GFile>::*gKeepFilePtrRaw[])(GFile*) = {&GPtr<GFile>::SetRaw};
GFile* (GPtr<GFile>::*gKeepFilePtrGet[])() const = {&GPtr<GFile>::GetPtr};
GImage* (GPtr<GImage>::*gKeepImagePtrGet[])() const = {&GPtr<GImage>::GetPtr};
GRefCountBaseImpl* (GPtr<GRefCountBaseImpl>::*gKeepBasePtrGet[])() const = {&GPtr<GRefCountBaseImpl>::GetPtr};
GPtr<GFile>& (GPtr<GFile>::*gKeepFilePtrAssign[])(GFile*) = {&GPtr<GFile>::operator=, &GPtr<GFile>::SetCounted};

// FUNCTION: ENGINE 0x1095BD50 ; GPtr<class GFile>::GPtr
#pragma inline_depth(0)
GPtr<GFile>* KeepFilePtrConstructor(GFile* file)
{
	return new GPtr<GFile>(file);
}
#pragma inline_depth()

// FUNCTION: ENGINE 0x1095BD30 ; GRefCountBase<class GFile>::GRefCountBase<class GFile>
#pragma inline_depth(0)
GRefCountBase<GFile>* KeepFileBaseConstructor()
{
	return new GRefCountBase<GFile>;
}
#pragma inline_depth()
