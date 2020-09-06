// Copyright (c) 2020 Pierre Fourgeaud
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

// -----------------------------------------------------------
// This file was generated following the 4.6 headers taken
// from the OpenGL Khronos registry on the 3/22/2020.
//
// NOTE: Extensions are not taken into account yet. This is
// something to add when we start using some.
// -----------------------------------------------------------

#pragma once

#include <GL/glcorearb.h>

#include "renderer/GL/GLAPI.h"

// Defines all function available in OpenGL core API
#define GL_1_0(Macro)                                                 \
    Macro(PFNGLCULLFACEPROC, glCullFace);                             \
    Macro(PFNGLFRONTFACEPROC, glFrontFace);                           \
    Macro(PFNGLHINTPROC, glHint);                                     \
    Macro(PFNGLLINEWIDTHPROC, glLineWidth);                           \
    Macro(PFNGLPOINTSIZEPROC, glPointSize);                           \
    Macro(PFNGLPOLYGONMODEPROC, glPolygonMode);                       \
    Macro(PFNGLSCISSORPROC, glScissor);                               \
    Macro(PFNGLTEXPARAMETERFPROC, glTexParameterf);                   \
    Macro(PFNGLTEXPARAMETERFVPROC, glTexParameterfv);                 \
    Macro(PFNGLTEXPARAMETERIPROC, glTexParameteri);                   \
    Macro(PFNGLTEXPARAMETERIVPROC, glTexParameteriv);                 \
    Macro(PFNGLTEXIMAGE1DPROC, glTexImage1D);                         \
    Macro(PFNGLTEXIMAGE2DPROC, glTexImage2D);                         \
    Macro(PFNGLDRAWBUFFERPROC, glDrawBuffer);                         \
    Macro(PFNGLCLEARPROC, glClear);                                   \
    Macro(PFNGLCLEARCOLORPROC, glClearColor);                         \
    Macro(PFNGLCLEARSTENCILPROC, glClearStencil);                     \
    Macro(PFNGLCLEARDEPTHPROC, glClearDepth);                         \
    Macro(PFNGLSTENCILMASKPROC, glStencilMask);                       \
    Macro(PFNGLCOLORMASKPROC, glColorMask);                           \
    Macro(PFNGLDEPTHMASKPROC, glDepthMask);                           \
    Macro(PFNGLDISABLEPROC, glDisable);                               \
    Macro(PFNGLENABLEPROC, glEnable);                                 \
    Macro(PFNGLFINISHPROC, glFinish);                                 \
    Macro(PFNGLFLUSHPROC, glFlush);                                   \
    Macro(PFNGLBLENDFUNCPROC, glBlendFunc);                           \
    Macro(PFNGLLOGICOPPROC, glLogicOp);                               \
    Macro(PFNGLSTENCILFUNCPROC, glStencilFunc);                       \
    Macro(PFNGLSTENCILOPPROC, glStencilOp);                           \
    Macro(PFNGLDEPTHFUNCPROC, glDepthFunc);                           \
    Macro(PFNGLPIXELSTOREFPROC, glPixelStoref);                       \
    Macro(PFNGLPIXELSTOREIPROC, glPixelStorei);                       \
    Macro(PFNGLREADBUFFERPROC, glReadBuffer);                         \
    Macro(PFNGLREADPIXELSPROC, glReadPixels);                         \
    Macro(PFNGLGETBOOLEANVPROC, glGetBooleanv);                       \
    Macro(PFNGLGETDOUBLEVPROC, glGetDoublev);                         \
    Macro(PFNGLGETERRORPROC, glGetError);                             \
    Macro(PFNGLGETFLOATVPROC, glGetFloatv);                           \
    Macro(PFNGLGETINTEGERVPROC, glGetIntegerv);                       \
    Macro(PFNGLGETSTRINGPROC, glGetString);                           \
    Macro(PFNGLGETTEXIMAGEPROC, glGetTexImage);                       \
    Macro(PFNGLGETTEXPARAMETERFVPROC, glGetTexParameterfv);           \
    Macro(PFNGLGETTEXPARAMETERIVPROC, glGetTexParameteriv);           \
    Macro(PFNGLGETTEXLEVELPARAMETERFVPROC, glGetTexLevelParameterfv); \
    Macro(PFNGLGETTEXLEVELPARAMETERIVPROC, glGetTexLevelParameteriv); \
    Macro(PFNGLISENABLEDPROC, glIsEnabled);                           \
    Macro(PFNGLDEPTHRANGEPROC, glDepthRange);                         \
    Macro(PFNGLVIEWPORTPROC, glViewport)

#define GL_1_1(Macro)                                       \
    Macro(PFNGLDRAWARRAYSPROC, glDrawArrays);               \
    Macro(PFNGLDRAWELEMENTSPROC, glDrawElements);           \
    Macro(PFNGLGETPOINTERVPROC, glGetPointerv);             \
    Macro(PFNGLPOLYGONOFFSETPROC, glPolygonOffset);         \
    Macro(PFNGLCOPYTEXIMAGE1DPROC, glCopyTexImage1D);       \
    Macro(PFNGLCOPYTEXIMAGE2DPROC, glCopyTexImage2D);       \
    Macro(PFNGLCOPYTEXSUBIMAGE1DPROC, glCopyTexSubImage1D); \
    Macro(PFNGLCOPYTEXSUBIMAGE2DPROC, glCopyTexSubImage2D); \
    Macro(PFNGLTEXSUBIMAGE1DPROC, glTexSubImage1D);         \
    Macro(PFNGLTEXSUBIMAGE2DPROC, glTexSubImage2D);         \
    Macro(PFNGLBINDTEXTUREPROC, glBindTexture);             \
    Macro(PFNGLDELETETEXTURESPROC, glDeleteTextures);       \
    Macro(PFNGLGENTEXTURESPROC, glGenTextures);             \
    Macro(PFNGLISTEXTUREPROC, glIsTexture)

#define GL_1_2(Macro)                                       \
    Macro(PFNGLDRAWRANGEELEMENTSPROC, glDrawRangeElements); \
    Macro(PFNGLTEXIMAGE3DPROC, glTexImage3D);               \
    Macro(PFNGLTEXSUBIMAGE3DPROC, glTexSubImage3D);         \
    Macro(PFNGLCOPYTEXSUBIMAGE3DPROC, glCopyTexSubImage3D)

#define GL_1_3(Macro)                                                   \
    Macro(PFNGLACTIVETEXTUREPROC, glActiveTexture);                     \
    Macro(PFNGLSAMPLECOVERAGEPROC, glSampleCoverage);                   \
    Macro(PFNGLCOMPRESSEDTEXIMAGE3DPROC, glCompressedTexImage3D);       \
    Macro(PFNGLCOMPRESSEDTEXIMAGE2DPROC, glCompressedTexImage2D);       \
    Macro(PFNGLCOMPRESSEDTEXIMAGE1DPROC, glCompressedTexImage1D);       \
    Macro(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC, glCompressedTexSubImage3D); \
    Macro(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC, glCompressedTexSubImage2D); \
    Macro(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC, glCompressedTexSubImage1D); \
    Macro(PFNGLGETCOMPRESSEDTEXIMAGEPROC, glGetCompressedTexImage)

#define GL_1_4(Macro)                                       \
    Macro(PFNGLBLENDFUNCSEPARATEPROC, glBlendFuncSeparate); \
    Macro(PFNGLMULTIDRAWARRAYSPROC, glMultiDrawArrays);     \
    Macro(PFNGLMULTIDRAWELEMENTSPROC, glMultiDrawElements); \
    Macro(PFNGLPOINTPARAMETERFPROC, glPointParameterf);     \
    Macro(PFNGLPOINTPARAMETERFVPROC, glPointParameterfv);   \
    Macro(PFNGLPOINTPARAMETERIPROC, glPointParameteri);     \
    Macro(PFNGLPOINTPARAMETERIVPROC, glPointParameteriv);   \
    Macro(PFNGLBLENDCOLORPROC, glBlendColor);               \
    Macro(PFNGLBLENDEQUATIONPROC, glBlendEquation)

#define GL_1_5(Macro)                                             \
    Macro(PFNGLGENQUERIESPROC, glGenQueries);                     \
    Macro(PFNGLDELETEQUERIESPROC, glDeleteQueries);               \
    Macro(PFNGLISQUERYPROC, glIsQuery);                           \
    Macro(PFNGLBEGINQUERYPROC, glBeginQuery);                     \
    Macro(PFNGLENDQUERYPROC, glEndQuery);                         \
    Macro(PFNGLGETQUERYIVPROC, glGetQueryiv);                     \
    Macro(PFNGLGETQUERYOBJECTIVPROC, glGetQueryObjectiv);         \
    Macro(PFNGLGETQUERYOBJECTUIVPROC, glGetQueryObjectuiv);       \
    Macro(PFNGLBINDBUFFERPROC, glBindBuffer);                     \
    Macro(PFNGLDELETEBUFFERSPROC, glDeleteBuffers);               \
    Macro(PFNGLGENBUFFERSPROC, glGenBuffers);                     \
    Macro(PFNGLISBUFFERPROC, glIsBuffer);                         \
    Macro(PFNGLBUFFERDATAPROC, glBufferData);                     \
    Macro(PFNGLBUFFERSUBDATAPROC, glBufferSubData);               \
    Macro(PFNGLGETBUFFERSUBDATAPROC, glGetBufferSubData);         \
    Macro(PFNGLMAPBUFFERPROC, glMapBuffer);                       \
    Macro(PFNGLUNMAPBUFFERPROC, glUnmapBuffer);                   \
    Macro(PFNGLGETBUFFERPARAMETERIVPROC, glGetBufferParameteriv); \
    Macro(PFNGLGETBUFFERPOINTERVPROC, glGetBufferPointerv)

#define GL_2_0(Macro)                                                     \
    Macro(PFNGLBLENDEQUATIONSEPARATEPROC, glBlendEquationSeparate);       \
    Macro(PFNGLDRAWBUFFERSPROC, glDrawBuffers);                           \
    Macro(PFNGLSTENCILOPSEPARATEPROC, glStencilOpSeparate);               \
    Macro(PFNGLSTENCILFUNCSEPARATEPROC, glStencilFuncSeparate);           \
    Macro(PFNGLSTENCILMASKSEPARATEPROC, glStencilMaskSeparate);           \
    Macro(PFNGLATTACHSHADERPROC, glAttachShader);                         \
    Macro(PFNGLBINDATTRIBLOCATIONPROC, glBindAttribLocation);             \
    Macro(PFNGLCOMPILESHADERPROC, glCompileShader);                       \
    Macro(PFNGLCREATEPROGRAMPROC, glCreateProgram);                       \
    Macro(PFNGLCREATESHADERPROC, glCreateShader);                         \
    Macro(PFNGLDELETEPROGRAMPROC, glDeleteProgram);                       \
    Macro(PFNGLDELETESHADERPROC, glDeleteShader);                         \
    Macro(PFNGLDETACHSHADERPROC, glDetachShader);                         \
    Macro(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray); \
    Macro(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray);   \
    Macro(PFNGLGETACTIVEATTRIBPROC, glGetActiveAttrib);                   \
    Macro(PFNGLGETACTIVEUNIFORMPROC, glGetActiveUniform);                 \
    Macro(PFNGLGETATTACHEDSHADERSPROC, glGetAttachedShaders);             \
    Macro(PFNGLGETATTRIBLOCATIONPROC, glGetAttribLocation);               \
    Macro(PFNGLGETPROGRAMIVPROC, glGetProgramiv);                         \
    Macro(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog);               \
    Macro(PFNGLGETSHADERIVPROC, glGetShaderiv);                           \
    Macro(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog);                 \
    Macro(PFNGLGETSHADERSOURCEPROC, glGetShaderSource);                   \
    Macro(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation);             \
    Macro(PFNGLGETUNIFORMFVPROC, glGetUniformfv);                         \
    Macro(PFNGLGETUNIFORMIVPROC, glGetUniformiv);                         \
    Macro(PFNGLGETVERTEXATTRIBDVPROC, glGetVertexAttribdv);               \
    Macro(PFNGLGETVERTEXATTRIBFVPROC, glGetVertexAttribfv);               \
    Macro(PFNGLGETVERTEXATTRIBIVPROC, glGetVertexAttribiv);               \
    Macro(PFNGLGETVERTEXATTRIBPOINTERVPROC, glGetVertexAttribPointerv);   \
    Macro(PFNGLISPROGRAMPROC, glIsProgram);                               \
    Macro(PFNGLISSHADERPROC, glIsShader);                                 \
    Macro(PFNGLLINKPROGRAMPROC, glLinkProgram);                           \
    Macro(PFNGLSHADERSOURCEPROC, glShaderSource);                         \
    Macro(PFNGLUSEPROGRAMPROC, glUseProgram);                             \
    Macro(PFNGLUNIFORM1FPROC, glUniform1f);                               \
    Macro(PFNGLUNIFORM2FPROC, glUniform2f);                               \
    Macro(PFNGLUNIFORM3FPROC, glUniform3f);                               \
    Macro(PFNGLUNIFORM4FPROC, glUniform4f);                               \
    Macro(PFNGLUNIFORM1IPROC, glUniform1i);                               \
    Macro(PFNGLUNIFORM2IPROC, glUniform2i);                               \
    Macro(PFNGLUNIFORM3IPROC, glUniform3i);                               \
    Macro(PFNGLUNIFORM4IPROC, glUniform4i);                               \
    Macro(PFNGLUNIFORM1FVPROC, glUniform1fv);                             \
    Macro(PFNGLUNIFORM2FVPROC, glUniform2fv);                             \
    Macro(PFNGLUNIFORM3FVPROC, glUniform3fv);                             \
    Macro(PFNGLUNIFORM4FVPROC, glUniform4fv);                             \
    Macro(PFNGLUNIFORM1IVPROC, glUniform1iv);                             \
    Macro(PFNGLUNIFORM2IVPROC, glUniform2iv);                             \
    Macro(PFNGLUNIFORM3IVPROC, glUniform3iv);                             \
    Macro(PFNGLUNIFORM4IVPROC, glUniform4iv);                             \
    Macro(PFNGLUNIFORMMATRIX2FVPROC, glUniformMatrix2fv);                 \
    Macro(PFNGLUNIFORMMATRIX3FVPROC, glUniformMatrix3fv);                 \
    Macro(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv);                 \
    Macro(PFNGLVALIDATEPROGRAMPROC, glValidateProgram);                   \
    Macro(PFNGLVERTEXATTRIB1DPROC, glVertexAttrib1d);                     \
    Macro(PFNGLVERTEXATTRIB1DVPROC, glVertexAttrib1dv);                   \
    Macro(PFNGLVERTEXATTRIB1FPROC, glVertexAttrib1f);                     \
    Macro(PFNGLVERTEXATTRIB1FVPROC, glVertexAttrib1fv);                   \
    Macro(PFNGLVERTEXATTRIB1SPROC, glVertexAttrib1s);                     \
    Macro(PFNGLVERTEXATTRIB1SVPROC, glVertexAttrib1sv);                   \
    Macro(PFNGLVERTEXATTRIB2DPROC, glVertexAttrib2d);                     \
    Macro(PFNGLVERTEXATTRIB2DVPROC, glVertexAttrib2dv);                   \
    Macro(PFNGLVERTEXATTRIB2FPROC, glVertexAttrib2f);                     \
    Macro(PFNGLVERTEXATTRIB2FVPROC, glVertexAttrib2fv);                   \
    Macro(PFNGLVERTEXATTRIB2SPROC, glVertexAttrib2s);                     \
    Macro(PFNGLVERTEXATTRIB2SVPROC, glVertexAttrib2sv);                   \
    Macro(PFNGLVERTEXATTRIB3DPROC, glVertexAttrib3d);                     \
    Macro(PFNGLVERTEXATTRIB3DVPROC, glVertexAttrib3dv);                   \
    Macro(PFNGLVERTEXATTRIB3FPROC, glVertexAttrib3f);                     \
    Macro(PFNGLVERTEXATTRIB3FVPROC, glVertexAttrib3fv);                   \
    Macro(PFNGLVERTEXATTRIB3SPROC, glVertexAttrib3s);                     \
    Macro(PFNGLVERTEXATTRIB3SVPROC, glVertexAttrib3sv);                   \
    Macro(PFNGLVERTEXATTRIB4NBVPROC, glVertexAttrib4Nbv);                 \
    Macro(PFNGLVERTEXATTRIB4NIVPROC, glVertexAttrib4Niv);                 \
    Macro(PFNGLVERTEXATTRIB4NSVPROC, glVertexAttrib4Nsv);                 \
    Macro(PFNGLVERTEXATTRIB4NUBPROC, glVertexAttrib4Nub);                 \
    Macro(PFNGLVERTEXATTRIB4NUBVPROC, glVertexAttrib4Nubv);               \
    Macro(PFNGLVERTEXATTRIB4NUIVPROC, glVertexAttrib4Nuiv);               \
    Macro(PFNGLVERTEXATTRIB4NUSVPROC, glVertexAttrib4Nusv);               \
    Macro(PFNGLVERTEXATTRIB4BVPROC, glVertexAttrib4bv);                   \
    Macro(PFNGLVERTEXATTRIB4DPROC, glVertexAttrib4d);                     \
    Macro(PFNGLVERTEXATTRIB4DVPROC, glVertexAttrib4dv);                   \
    Macro(PFNGLVERTEXATTRIB4FPROC, glVertexAttrib4f);                     \
    Macro(PFNGLVERTEXATTRIB4FVPROC, glVertexAttrib4fv);                   \
    Macro(PFNGLVERTEXATTRIB4IVPROC, glVertexAttrib4iv);                   \
    Macro(PFNGLVERTEXATTRIB4SPROC, glVertexAttrib4s);                     \
    Macro(PFNGLVERTEXATTRIB4SVPROC, glVertexAttrib4sv);                   \
    Macro(PFNGLVERTEXATTRIB4UBVPROC, glVertexAttrib4ubv);                 \
    Macro(PFNGLVERTEXATTRIB4UIVPROC, glVertexAttrib4uiv);                 \
    Macro(PFNGLVERTEXATTRIB4USVPROC, glVertexAttrib4usv);                 \
    Macro(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)

#define GL_2_1(Macro)                                         \
    Macro(PFNGLUNIFORMMATRIX2X3FVPROC, glUniformMatrix2x3fv); \
    Macro(PFNGLUNIFORMMATRIX3X2FVPROC, glUniformMatrix3x2fv); \
    Macro(PFNGLUNIFORMMATRIX2X4FVPROC, glUniformMatrix2x4fv); \
    Macro(PFNGLUNIFORMMATRIX4X2FVPROC, glUniformMatrix4x2fv); \
    Macro(PFNGLUNIFORMMATRIX3X4FVPROC, glUniformMatrix3x4fv); \
    Macro(PFNGLUNIFORMMATRIX4X3FVPROC, glUniformMatrix4x3fv)

#define GL_3_0(Macro)                                                                           \
    Macro(PFNGLCOLORMASKIPROC, glColorMaski);                                                   \
    Macro(PFNGLGETBOOLEANI_VPROC, glGetBooleani_v);                                             \
    Macro(PFNGLGETINTEGERI_VPROC, glGetIntegeri_v);                                             \
    Macro(PFNGLENABLEIPROC, glEnablei);                                                         \
    Macro(PFNGLDISABLEIPROC, glDisablei);                                                       \
    Macro(PFNGLISENABLEDIPROC, glIsEnabledi);                                                   \
    Macro(PFNGLBEGINTRANSFORMFEEDBACKPROC, glBeginTransformFeedback);                           \
    Macro(PFNGLENDTRANSFORMFEEDBACKPROC, glEndTransformFeedback);                               \
    Macro(PFNGLBINDBUFFERRANGEPROC, glBindBufferRange);                                         \
    Macro(PFNGLBINDBUFFERBASEPROC, glBindBufferBase);                                           \
    Macro(PFNGLTRANSFORMFEEDBACKVARYINGSPROC, glTransformFeedbackVaryings);                     \
    Macro(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC, glGetTransformFeedbackVarying);                 \
    Macro(PFNGLCLAMPCOLORPROC, glClampColor);                                                   \
    Macro(PFNGLBEGINCONDITIONALRENDERPROC, glBeginConditionalRender);                           \
    Macro(PFNGLENDCONDITIONALRENDERPROC, glEndConditionalRender);                               \
    Macro(PFNGLVERTEXATTRIBIPOINTERPROC, glVertexAttribIPointer);                               \
    Macro(PFNGLGETVERTEXATTRIBIIVPROC, glGetVertexAttribIiv);                                   \
    Macro(PFNGLGETVERTEXATTRIBIUIVPROC, glGetVertexAttribIuiv);                                 \
    Macro(PFNGLVERTEXATTRIBI1IPROC, glVertexAttribI1i);                                         \
    Macro(PFNGLVERTEXATTRIBI2IPROC, glVertexAttribI2i);                                         \
    Macro(PFNGLVERTEXATTRIBI3IPROC, glVertexAttribI3i);                                         \
    Macro(PFNGLVERTEXATTRIBI4IPROC, glVertexAttribI4i);                                         \
    Macro(PFNGLVERTEXATTRIBI1UIPROC, glVertexAttribI1ui);                                       \
    Macro(PFNGLVERTEXATTRIBI2UIPROC, glVertexAttribI2ui);                                       \
    Macro(PFNGLVERTEXATTRIBI3UIPROC, glVertexAttribI3ui);                                       \
    Macro(PFNGLVERTEXATTRIBI4UIPROC, glVertexAttribI4ui);                                       \
    Macro(PFNGLVERTEXATTRIBI1IVPROC, glVertexAttribI1iv);                                       \
    Macro(PFNGLVERTEXATTRIBI2IVPROC, glVertexAttribI2iv);                                       \
    Macro(PFNGLVERTEXATTRIBI3IVPROC, glVertexAttribI3iv);                                       \
    Macro(PFNGLVERTEXATTRIBI4IVPROC, glVertexAttribI4iv);                                       \
    Macro(PFNGLVERTEXATTRIBI1UIVPROC, glVertexAttribI1uiv);                                     \
    Macro(PFNGLVERTEXATTRIBI2UIVPROC, glVertexAttribI2uiv);                                     \
    Macro(PFNGLVERTEXATTRIBI3UIVPROC, glVertexAttribI3uiv);                                     \
    Macro(PFNGLVERTEXATTRIBI4UIVPROC, glVertexAttribI4uiv);                                     \
    Macro(PFNGLVERTEXATTRIBI4BVPROC, glVertexAttribI4bv);                                       \
    Macro(PFNGLVERTEXATTRIBI4SVPROC, glVertexAttribI4sv);                                       \
    Macro(PFNGLVERTEXATTRIBI4UBVPROC, glVertexAttribI4ubv);                                     \
    Macro(PFNGLVERTEXATTRIBI4USVPROC, glVertexAttribI4usv);                                     \
    Macro(PFNGLGETUNIFORMUIVPROC, glGetUniformuiv);                                             \
    Macro(PFNGLBINDFRAGDATALOCATIONPROC, glBindFragDataLocation);                               \
    Macro(PFNGLGETFRAGDATALOCATIONPROC, glGetFragDataLocation);                                 \
    Macro(PFNGLUNIFORM1UIPROC, glUniform1ui);                                                   \
    Macro(PFNGLUNIFORM2UIPROC, glUniform2ui);                                                   \
    Macro(PFNGLUNIFORM3UIPROC, glUniform3ui);                                                   \
    Macro(PFNGLUNIFORM4UIPROC, glUniform4ui);                                                   \
    Macro(PFNGLUNIFORM1UIVPROC, glUniform1uiv);                                                 \
    Macro(PFNGLUNIFORM2UIVPROC, glUniform2uiv);                                                 \
    Macro(PFNGLUNIFORM3UIVPROC, glUniform3uiv);                                                 \
    Macro(PFNGLUNIFORM4UIVPROC, glUniform4uiv);                                                 \
    Macro(PFNGLTEXPARAMETERIIVPROC, glTexParameterIiv);                                         \
    Macro(PFNGLTEXPARAMETERIUIVPROC, glTexParameterIuiv);                                       \
    Macro(PFNGLGETTEXPARAMETERIIVPROC, glGetTexParameterIiv);                                   \
    Macro(PFNGLGETTEXPARAMETERIUIVPROC, glGetTexParameterIuiv);                                 \
    Macro(PFNGLCLEARBUFFERIVPROC, glClearBufferiv);                                             \
    Macro(PFNGLCLEARBUFFERUIVPROC, glClearBufferuiv);                                           \
    Macro(PFNGLCLEARBUFFERFVPROC, glClearBufferfv);                                             \
    Macro(PFNGLCLEARBUFFERFIPROC, glClearBufferfi);                                             \
    Macro(PFNGLGETSTRINGIPROC, glGetStringi);                                                   \
    Macro(PFNGLISRENDERBUFFERPROC, glIsRenderbuffer);                                           \
    Macro(PFNGLBINDRENDERBUFFERPROC, glBindRenderbuffer);                                       \
    Macro(PFNGLDELETERENDERBUFFERSPROC, glDeleteRenderbuffers);                                 \
    Macro(PFNGLGENRENDERBUFFERSPROC, glGenRenderbuffers);                                       \
    Macro(PFNGLRENDERBUFFERSTORAGEPROC, glRenderbufferStorage);                                 \
    Macro(PFNGLGETRENDERBUFFERPARAMETERIVPROC, glGetRenderbufferParameteriv);                   \
    Macro(PFNGLISFRAMEBUFFERPROC, glIsFramebuffer);                                             \
    Macro(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer);                                         \
    Macro(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers);                                   \
    Macro(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers);                                         \
    Macro(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatus);                           \
    Macro(PFNGLFRAMEBUFFERTEXTURE1DPROC, glFramebufferTexture1D);                               \
    Macro(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D);                               \
    Macro(PFNGLFRAMEBUFFERTEXTURE3DPROC, glFramebufferTexture3D);                               \
    Macro(PFNGLFRAMEBUFFERRENDERBUFFERPROC, glFramebufferRenderbuffer);                         \
    Macro(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC, glGetFramebufferAttachmentParameteriv); \
    Macro(PFNGLGENERATEMIPMAPPROC, glGenerateMipmap);                                           \
    Macro(PFNGLBLITFRAMEBUFFERPROC, glBlitFramebuffer);                                         \
    Macro(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC, glRenderbufferStorageMultisample);           \
    Macro(PFNGLFRAMEBUFFERTEXTURELAYERPROC, glFramebufferTextureLayer);                         \
    Macro(PFNGLMAPBUFFERRANGEPROC, glMapBufferRange);                                           \
    Macro(PFNGLFLUSHMAPPEDBUFFERRANGEPROC, glFlushMappedBufferRange);                           \
    Macro(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray);                                         \
    Macro(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays);                                   \
    Macro(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays);                                         \
    Macro(PFNGLISVERTEXARRAYPROC, glIsVertexArray)

#define GL_3_1(Macro)                                                       \
    Macro(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstanced);             \
    Macro(PFNGLDRAWELEMENTSINSTANCEDPROC, glDrawElementsInstanced);         \
    Macro(PFNGLTEXBUFFERPROC, glTexBuffer);                                 \
    Macro(PFNGLPRIMITIVERESTARTINDEXPROC, glPrimitiveRestartIndex);         \
    Macro(PFNGLCOPYBUFFERSUBDATAPROC, glCopyBufferSubData);                 \
    Macro(PFNGLGETUNIFORMINDICESPROC, glGetUniformIndices);                 \
    Macro(PFNGLGETACTIVEUNIFORMSIVPROC, glGetActiveUniformsiv);             \
    Macro(PFNGLGETACTIVEUNIFORMNAMEPROC, glGetActiveUniformName);           \
    Macro(PFNGLGETUNIFORMBLOCKINDEXPROC, glGetUniformBlockIndex);           \
    Macro(PFNGLGETACTIVEUNIFORMBLOCKIVPROC, glGetActiveUniformBlockiv);     \
    Macro(PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC, glGetActiveUniformBlockName); \
    Macro(PFNGLUNIFORMBLOCKBINDINGPROC, glUniformBlockBinding)

#define GL_3_2(Macro)                                                                   \
    Macro(PFNGLDRAWELEMENTSBASEVERTEXPROC, glDrawElementsBaseVertex);                   \
    Macro(PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC, glDrawRangeElementsBaseVertex);         \
    Macro(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC, glDrawElementsInstancedBaseVertex); \
    Macro(PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC, glMultiDrawElementsBaseVertex);         \
    Macro(PFNGLPROVOKINGVERTEXPROC, glProvokingVertex);                                 \
    Macro(PFNGLFENCESYNCPROC, glFenceSync);                                             \
    Macro(PFNGLISSYNCPROC, glIsSync);                                                   \
    Macro(PFNGLDELETESYNCPROC, glDeleteSync);                                           \
    Macro(PFNGLCLIENTWAITSYNCPROC, glClientWaitSync);                                   \
    Macro(PFNGLWAITSYNCPROC, glWaitSync);                                               \
    Macro(PFNGLGETINTEGER64VPROC, glGetInteger64v);                                     \
    Macro(PFNGLGETSYNCIVPROC, glGetSynciv);                                             \
    Macro(PFNGLGETINTEGER64I_VPROC, glGetInteger64i_v);                                 \
    Macro(PFNGLGETBUFFERPARAMETERI64VPROC, glGetBufferParameteri64v);                   \
    Macro(PFNGLFRAMEBUFFERTEXTUREPROC, glFramebufferTexture);                           \
    Macro(PFNGLTEXIMAGE2DMULTISAMPLEPROC, glTexImage2DMultisample);                     \
    Macro(PFNGLTEXIMAGE3DMULTISAMPLEPROC, glTexImage3DMultisample);                     \
    Macro(PFNGLGETMULTISAMPLEFVPROC, glGetMultisamplefv);                               \
    Macro(PFNGLSAMPLEMASKIPROC, glSampleMaski)

#define GL_3_3(Macro)                                                           \
    Macro(PFNGLBINDFRAGDATALOCATIONINDEXEDPROC, glBindFragDataLocationIndexed); \
    Macro(PFNGLGETFRAGDATAINDEXPROC, glGetFragDataIndex);                       \
    Macro(PFNGLGENSAMPLERSPROC, glGenSamplers);                                 \
    Macro(PFNGLDELETESAMPLERSPROC, glDeleteSamplers);                           \
    Macro(PFNGLISSAMPLERPROC, glIsSampler);                                     \
    Macro(PFNGLBINDSAMPLERPROC, glBindSampler);                                 \
    Macro(PFNGLSAMPLERPARAMETERIPROC, glSamplerParameteri);                     \
    Macro(PFNGLSAMPLERPARAMETERIVPROC, glSamplerParameteriv);                   \
    Macro(PFNGLSAMPLERPARAMETERFPROC, glSamplerParameterf);                     \
    Macro(PFNGLSAMPLERPARAMETERFVPROC, glSamplerParameterfv);                   \
    Macro(PFNGLSAMPLERPARAMETERIIVPROC, glSamplerParameterIiv);                 \
    Macro(PFNGLSAMPLERPARAMETERIUIVPROC, glSamplerParameterIuiv);               \
    Macro(PFNGLGETSAMPLERPARAMETERIVPROC, glGetSamplerParameteriv);             \
    Macro(PFNGLGETSAMPLERPARAMETERIIVPROC, glGetSamplerParameterIiv);           \
    Macro(PFNGLGETSAMPLERPARAMETERFVPROC, glGetSamplerParameterfv);             \
    Macro(PFNGLGETSAMPLERPARAMETERIUIVPROC, glGetSamplerParameterIuiv);         \
    Macro(PFNGLQUERYCOUNTERPROC, glQueryCounter);                               \
    Macro(PFNGLGETQUERYOBJECTI64VPROC, glGetQueryObjecti64v);                   \
    Macro(PFNGLGETQUERYOBJECTUI64VPROC, glGetQueryObjectui64v);                 \
    Macro(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisor);                 \
    Macro(PFNGLVERTEXATTRIBP1UIPROC, glVertexAttribP1ui);                       \
    Macro(PFNGLVERTEXATTRIBP1UIVPROC, glVertexAttribP1uiv);                     \
    Macro(PFNGLVERTEXATTRIBP2UIPROC, glVertexAttribP2ui);                       \
    Macro(PFNGLVERTEXATTRIBP2UIVPROC, glVertexAttribP2uiv);                     \
    Macro(PFNGLVERTEXATTRIBP3UIPROC, glVertexAttribP3ui);                       \
    Macro(PFNGLVERTEXATTRIBP3UIVPROC, glVertexAttribP3uiv);                     \
    Macro(PFNGLVERTEXATTRIBP4UIPROC, glVertexAttribP4ui);                       \
    Macro(PFNGLVERTEXATTRIBP4UIVPROC, glVertexAttribP4uiv)

#define GL_4_0(Macro)                                                                 \
    Macro(PFNGLMINSAMPLESHADINGPROC, glMinSampleShading);                             \
    Macro(PFNGLBLENDEQUATIONIPROC, glBlendEquationi);                                 \
    Macro(PFNGLBLENDEQUATIONSEPARATEIPROC, glBlendEquationSeparatei);                 \
    Macro(PFNGLBLENDFUNCIPROC, glBlendFunci);                                         \
    Macro(PFNGLBLENDFUNCSEPARATEIPROC, glBlendFuncSeparatei);                         \
    Macro(PFNGLDRAWARRAYSINDIRECTPROC, glDrawArraysIndirect);                         \
    Macro(PFNGLDRAWELEMENTSINDIRECTPROC, glDrawElementsIndirect);                     \
    Macro(PFNGLUNIFORM1DPROC, glUniform1d);                                           \
    Macro(PFNGLUNIFORM2DPROC, glUniform2d);                                           \
    Macro(PFNGLUNIFORM3DPROC, glUniform3d);                                           \
    Macro(PFNGLUNIFORM4DPROC, glUniform4d);                                           \
    Macro(PFNGLUNIFORM1DVPROC, glUniform1dv);                                         \
    Macro(PFNGLUNIFORM2DVPROC, glUniform2dv);                                         \
    Macro(PFNGLUNIFORM3DVPROC, glUniform3dv);                                         \
    Macro(PFNGLUNIFORM4DVPROC, glUniform4dv);                                         \
    Macro(PFNGLUNIFORMMATRIX2DVPROC, glUniformMatrix2dv);                             \
    Macro(PFNGLUNIFORMMATRIX3DVPROC, glUniformMatrix3dv);                             \
    Macro(PFNGLUNIFORMMATRIX4DVPROC, glUniformMatrix4dv);                             \
    Macro(PFNGLUNIFORMMATRIX2X3DVPROC, glUniformMatrix2x3dv);                         \
    Macro(PFNGLUNIFORMMATRIX2X4DVPROC, glUniformMatrix2x4dv);                         \
    Macro(PFNGLUNIFORMMATRIX3X2DVPROC, glUniformMatrix3x2dv);                         \
    Macro(PFNGLUNIFORMMATRIX3X4DVPROC, glUniformMatrix3x4dv);                         \
    Macro(PFNGLUNIFORMMATRIX4X2DVPROC, glUniformMatrix4x2dv);                         \
    Macro(PFNGLUNIFORMMATRIX4X3DVPROC, glUniformMatrix4x3dv);                         \
    Macro(PFNGLGETUNIFORMDVPROC, glGetUniformdv);                                     \
    Macro(PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC, glGetSubroutineUniformLocation);     \
    Macro(PFNGLGETSUBROUTINEINDEXPROC, glGetSubroutineIndex);                         \
    Macro(PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC, glGetActiveSubroutineUniformiv);     \
    Macro(PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC, glGetActiveSubroutineUniformName); \
    Macro(PFNGLGETACTIVESUBROUTINENAMEPROC, glGetActiveSubroutineName);               \
    Macro(PFNGLUNIFORMSUBROUTINESUIVPROC, glUniformSubroutinesuiv);                   \
    Macro(PFNGLGETUNIFORMSUBROUTINEUIVPROC, glGetUniformSubroutineuiv);               \
    Macro(PFNGLGETPROGRAMSTAGEIVPROC, glGetProgramStageiv);                           \
    Macro(PFNGLPATCHPARAMETERIPROC, glPatchParameteri);                               \
    Macro(PFNGLPATCHPARAMETERFVPROC, glPatchParameterfv);                             \
    Macro(PFNGLBINDTRANSFORMFEEDBACKPROC, glBindTransformFeedback);                   \
    Macro(PFNGLDELETETRANSFORMFEEDBACKSPROC, glDeleteTransformFeedbacks);             \
    Macro(PFNGLGENTRANSFORMFEEDBACKSPROC, glGenTransformFeedbacks);                   \
    Macro(PFNGLISTRANSFORMFEEDBACKPROC, glIsTransformFeedback);                       \
    Macro(PFNGLPAUSETRANSFORMFEEDBACKPROC, glPauseTransformFeedback);                 \
    Macro(PFNGLRESUMETRANSFORMFEEDBACKPROC, glResumeTransformFeedback);               \
    Macro(PFNGLDRAWTRANSFORMFEEDBACKPROC, glDrawTransformFeedback);                   \
    Macro(PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC, glDrawTransformFeedbackStream);       \
    Macro(PFNGLBEGINQUERYINDEXEDPROC, glBeginQueryIndexed);                           \
    Macro(PFNGLENDQUERYINDEXEDPROC, glEndQueryIndexed);                               \
    Macro(PFNGLGETQUERYINDEXEDIVPROC, glGetQueryIndexediv)

#define GL_4_1(Macro)                                                       \
    Macro(PFNGLRELEASESHADERCOMPILERPROC, glReleaseShaderCompiler);         \
    Macro(PFNGLSHADERBINARYPROC, glShaderBinary);                           \
    Macro(PFNGLGETSHADERPRECISIONFORMATPROC, glGetShaderPrecisionFormat);   \
    Macro(PFNGLDEPTHRANGEFPROC, glDepthRangef);                             \
    Macro(PFNGLCLEARDEPTHFPROC, glClearDepthf);                             \
    Macro(PFNGLGETPROGRAMBINARYPROC, glGetProgramBinary);                   \
    Macro(PFNGLPROGRAMBINARYPROC, glProgramBinary);                         \
    Macro(PFNGLPROGRAMPARAMETERIPROC, glProgramParameteri);                 \
    Macro(PFNGLUSEPROGRAMSTAGESPROC, glUseProgramStages);                   \
    Macro(PFNGLACTIVESHADERPROGRAMPROC, glActiveShaderProgram);             \
    Macro(PFNGLCREATESHADERPROGRAMVPROC, glCreateShaderProgramv);           \
    Macro(PFNGLBINDPROGRAMPIPELINEPROC, glBindProgramPipeline);             \
    Macro(PFNGLDELETEPROGRAMPIPELINESPROC, glDeleteProgramPipelines);       \
    Macro(PFNGLGENPROGRAMPIPELINESPROC, glGenProgramPipelines);             \
    Macro(PFNGLISPROGRAMPIPELINEPROC, glIsProgramPipeline);                 \
    Macro(PFNGLGETPROGRAMPIPELINEIVPROC, glGetProgramPipelineiv);           \
    Macro(PFNGLPROGRAMUNIFORM1IPROC, glProgramUniform1i);                   \
    Macro(PFNGLPROGRAMUNIFORM1IVPROC, glProgramUniform1iv);                 \
    Macro(PFNGLPROGRAMUNIFORM1FPROC, glProgramUniform1f);                   \
    Macro(PFNGLPROGRAMUNIFORM1FVPROC, glProgramUniform1fv);                 \
    Macro(PFNGLPROGRAMUNIFORM1DPROC, glProgramUniform1d);                   \
    Macro(PFNGLPROGRAMUNIFORM1DVPROC, glProgramUniform1dv);                 \
    Macro(PFNGLPROGRAMUNIFORM1UIPROC, glProgramUniform1ui);                 \
    Macro(PFNGLPROGRAMUNIFORM1UIVPROC, glProgramUniform1uiv);               \
    Macro(PFNGLPROGRAMUNIFORM2IPROC, glProgramUniform2i);                   \
    Macro(PFNGLPROGRAMUNIFORM2IVPROC, glProgramUniform2iv);                 \
    Macro(PFNGLPROGRAMUNIFORM2FPROC, glProgramUniform2f);                   \
    Macro(PFNGLPROGRAMUNIFORM2FVPROC, glProgramUniform2fv);                 \
    Macro(PFNGLPROGRAMUNIFORM2DPROC, glProgramUniform2d);                   \
    Macro(PFNGLPROGRAMUNIFORM2DVPROC, glProgramUniform2dv);                 \
    Macro(PFNGLPROGRAMUNIFORM2UIPROC, glProgramUniform2ui);                 \
    Macro(PFNGLPROGRAMUNIFORM2UIVPROC, glProgramUniform2uiv);               \
    Macro(PFNGLPROGRAMUNIFORM3IPROC, glProgramUniform3i);                   \
    Macro(PFNGLPROGRAMUNIFORM3IVPROC, glProgramUniform3iv);                 \
    Macro(PFNGLPROGRAMUNIFORM3FPROC, glProgramUniform3f);                   \
    Macro(PFNGLPROGRAMUNIFORM3FVPROC, glProgramUniform3fv);                 \
    Macro(PFNGLPROGRAMUNIFORM3DPROC, glProgramUniform3d);                   \
    Macro(PFNGLPROGRAMUNIFORM3DVPROC, glProgramUniform3dv);                 \
    Macro(PFNGLPROGRAMUNIFORM3UIPROC, glProgramUniform3ui);                 \
    Macro(PFNGLPROGRAMUNIFORM3UIVPROC, glProgramUniform3uiv);               \
    Macro(PFNGLPROGRAMUNIFORM4IPROC, glProgramUniform4i);                   \
    Macro(PFNGLPROGRAMUNIFORM4IVPROC, glProgramUniform4iv);                 \
    Macro(PFNGLPROGRAMUNIFORM4FPROC, glProgramUniform4f);                   \
    Macro(PFNGLPROGRAMUNIFORM4FVPROC, glProgramUniform4fv);                 \
    Macro(PFNGLPROGRAMUNIFORM4DPROC, glProgramUniform4d);                   \
    Macro(PFNGLPROGRAMUNIFORM4DVPROC, glProgramUniform4dv);                 \
    Macro(PFNGLPROGRAMUNIFORM4UIPROC, glProgramUniform4ui);                 \
    Macro(PFNGLPROGRAMUNIFORM4UIVPROC, glProgramUniform4uiv);               \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2FVPROC, glProgramUniformMatrix2fv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3FVPROC, glProgramUniformMatrix3fv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4FVPROC, glProgramUniformMatrix4fv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2DVPROC, glProgramUniformMatrix2dv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3DVPROC, glProgramUniformMatrix3dv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4DVPROC, glProgramUniformMatrix4dv);     \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC, glProgramUniformMatrix2x3fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC, glProgramUniformMatrix3x2fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC, glProgramUniformMatrix2x4fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC, glProgramUniformMatrix4x2fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC, glProgramUniformMatrix3x4fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC, glProgramUniformMatrix4x3fv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC, glProgramUniformMatrix2x3dv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC, glProgramUniformMatrix3x2dv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC, glProgramUniformMatrix2x4dv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC, glProgramUniformMatrix4x2dv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC, glProgramUniformMatrix3x4dv); \
    Macro(PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC, glProgramUniformMatrix4x3dv); \
    Macro(PFNGLVALIDATEPROGRAMPIPELINEPROC, glValidateProgramPipeline);     \
    Macro(PFNGLGETPROGRAMPIPELINEINFOLOGPROC, glGetProgramPipelineInfoLog); \
    Macro(PFNGLVERTEXATTRIBL1DPROC, glVertexAttribL1d);                     \
    Macro(PFNGLVERTEXATTRIBL2DPROC, glVertexAttribL2d);                     \
    Macro(PFNGLVERTEXATTRIBL3DPROC, glVertexAttribL3d);                     \
    Macro(PFNGLVERTEXATTRIBL4DPROC, glVertexAttribL4d);                     \
    Macro(PFNGLVERTEXATTRIBL1DVPROC, glVertexAttribL1dv);                   \
    Macro(PFNGLVERTEXATTRIBL2DVPROC, glVertexAttribL2dv);                   \
    Macro(PFNGLVERTEXATTRIBL3DVPROC, glVertexAttribL3dv);                   \
    Macro(PFNGLVERTEXATTRIBL4DVPROC, glVertexAttribL4dv);                   \
    Macro(PFNGLVERTEXATTRIBLPOINTERPROC, glVertexAttribLPointer);           \
    Macro(PFNGLGETVERTEXATTRIBLDVPROC, glGetVertexAttribLdv);               \
    Macro(PFNGLVIEWPORTARRAYVPROC, glViewportArrayv);                       \
    Macro(PFNGLVIEWPORTINDEXEDFPROC, glViewportIndexedf);                   \
    Macro(PFNGLVIEWPORTINDEXEDFVPROC, glViewportIndexedfv);                 \
    Macro(PFNGLSCISSORARRAYVPROC, glScissorArrayv);                         \
    Macro(PFNGLSCISSORINDEXEDPROC, glScissorIndexed);                       \
    Macro(PFNGLSCISSORINDEXEDVPROC, glScissorIndexedv);                     \
    Macro(PFNGLDEPTHRANGEARRAYVPROC, glDepthRangeArrayv);                   \
    Macro(PFNGLDEPTHRANGEINDEXEDPROC, glDepthRangeIndexed);                 \
    Macro(PFNGLGETFLOATI_VPROC, glGetFloati_v);                             \
    Macro(PFNGLGETDOUBLEI_VPROC, glGetDoublei_v)

#define GL_4_2(Macro)                                                                       \
    Macro(PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC, glDrawArraysInstancedBaseInstance);     \
    Macro(PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC, glDrawElementsInstancedBaseInstance); \
    Macro(PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC,                             \
          glDrawElementsInstancedBaseVertexBaseInstance);                                   \
    Macro(PFNGLGETINTERNALFORMATIVPROC, glGetInternalformativ);                             \
    Macro(PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC, glGetActiveAtomicCounterBufferiv);       \
    Macro(PFNGLBINDIMAGETEXTUREPROC, glBindImageTexture);                                   \
    Macro(PFNGLMEMORYBARRIERPROC, glMemoryBarrier);                                         \
    Macro(PFNGLTEXSTORAGE1DPROC, glTexStorage1D);                                           \
    Macro(PFNGLTEXSTORAGE2DPROC, glTexStorage2D);                                           \
    Macro(PFNGLTEXSTORAGE3DPROC, glTexStorage3D);                                           \
    Macro(PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC, glDrawTransformFeedbackInstanced);       \
    Macro(PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC, glDrawTransformFeedbackStreamInstanced)

#define GL_4_3(Macro)                                                                   \
    Macro(PFNGLCLEARBUFFERDATAPROC, glClearBufferData);                                 \
    Macro(PFNGLCLEARBUFFERSUBDATAPROC, glClearBufferSubData);                           \
    Macro(PFNGLDISPATCHCOMPUTEPROC, glDispatchCompute);                                 \
    Macro(PFNGLDISPATCHCOMPUTEINDIRECTPROC, glDispatchComputeIndirect);                 \
    Macro(PFNGLCOPYIMAGESUBDATAPROC, glCopyImageSubData);                               \
    Macro(PFNGLFRAMEBUFFERPARAMETERIPROC, glFramebufferParameteri);                     \
    Macro(PFNGLGETFRAMEBUFFERPARAMETERIVPROC, glGetFramebufferParameteriv);             \
    Macro(PFNGLGETINTERNALFORMATI64VPROC, glGetInternalformati64v);                     \
    Macro(PFNGLINVALIDATETEXSUBIMAGEPROC, glInvalidateTexSubImage);                     \
    Macro(PFNGLINVALIDATETEXIMAGEPROC, glInvalidateTexImage);                           \
    Macro(PFNGLINVALIDATEBUFFERSUBDATAPROC, glInvalidateBufferSubData);                 \
    Macro(PFNGLINVALIDATEBUFFERDATAPROC, glInvalidateBufferData);                       \
    Macro(PFNGLINVALIDATEFRAMEBUFFERPROC, glInvalidateFramebuffer);                     \
    Macro(PFNGLINVALIDATESUBFRAMEBUFFERPROC, glInvalidateSubFramebuffer);               \
    Macro(PFNGLMULTIDRAWARRAYSINDIRECTPROC, glMultiDrawArraysIndirect);                 \
    Macro(PFNGLMULTIDRAWELEMENTSINDIRECTPROC, glMultiDrawElementsIndirect);             \
    Macro(PFNGLGETPROGRAMINTERFACEIVPROC, glGetProgramInterfaceiv);                     \
    Macro(PFNGLGETPROGRAMRESOURCEINDEXPROC, glGetProgramResourceIndex);                 \
    Macro(PFNGLGETPROGRAMRESOURCENAMEPROC, glGetProgramResourceName);                   \
    Macro(PFNGLGETPROGRAMRESOURCEIVPROC, glGetProgramResourceiv);                       \
    Macro(PFNGLGETPROGRAMRESOURCELOCATIONPROC, glGetProgramResourceLocation);           \
    Macro(PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC, glGetProgramResourceLocationIndex); \
    Macro(PFNGLSHADERSTORAGEBLOCKBINDINGPROC, glShaderStorageBlockBinding);             \
    Macro(PFNGLTEXBUFFERRANGEPROC, glTexBufferRange);                                   \
    Macro(PFNGLTEXSTORAGE2DMULTISAMPLEPROC, glTexStorage2DMultisample);                 \
    Macro(PFNGLTEXSTORAGE3DMULTISAMPLEPROC, glTexStorage3DMultisample);                 \
    Macro(PFNGLTEXTUREVIEWPROC, glTextureView);                                         \
    Macro(PFNGLBINDVERTEXBUFFERPROC, glBindVertexBuffer);                               \
    Macro(PFNGLVERTEXATTRIBFORMATPROC, glVertexAttribFormat);                           \
    Macro(PFNGLVERTEXATTRIBIFORMATPROC, glVertexAttribIFormat);                         \
    Macro(PFNGLVERTEXATTRIBLFORMATPROC, glVertexAttribLFormat);                         \
    Macro(PFNGLVERTEXATTRIBBINDINGPROC, glVertexAttribBinding);                         \
    Macro(PFNGLVERTEXBINDINGDIVISORPROC, glVertexBindingDivisor);                       \
    Macro(PFNGLDEBUGMESSAGECONTROLPROC, glDebugMessageControl);                         \
    Macro(PFNGLDEBUGMESSAGEINSERTPROC, glDebugMessageInsert);                           \
    Macro(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback);                       \
    Macro(PFNGLGETDEBUGMESSAGELOGPROC, glGetDebugMessageLog);                           \
    Macro(PFNGLPUSHDEBUGGROUPPROC, glPushDebugGroup);                                   \
    Macro(PFNGLPOPDEBUGGROUPPROC, glPopDebugGroup);                                     \
    Macro(PFNGLOBJECTLABELPROC, glObjectLabel);                                         \
    Macro(PFNGLGETOBJECTLABELPROC, glGetObjectLabel);                                   \
    Macro(PFNGLOBJECTPTRLABELPROC, glObjectPtrLabel);                                   \
    Macro(PFNGLGETOBJECTPTRLABELPROC, glGetObjectPtrLabel)

#define GL_4_4(Macro)                                       \
    Macro(PFNGLBUFFERSTORAGEPROC, glBufferStorage);         \
    Macro(PFNGLCLEARTEXIMAGEPROC, glClearTexImage);         \
    Macro(PFNGLCLEARTEXSUBIMAGEPROC, glClearTexSubImage);   \
    Macro(PFNGLBINDBUFFERSBASEPROC, glBindBuffersBase);     \
    Macro(PFNGLBINDBUFFERSRANGEPROC, glBindBuffersRange);   \
    Macro(PFNGLBINDTEXTURESPROC, glBindTextures);           \
    Macro(PFNGLBINDSAMPLERSPROC, glBindSamplers);           \
    Macro(PFNGLBINDIMAGETEXTURESPROC, glBindImageTextures); \
    Macro(PFNGLBINDVERTEXBUFFERSPROC, glBindVertexBuffers)

#define GL_4_5(Macro)                                                                           \
    Macro(PFNGLCLIPCONTROLPROC, glClipControl);                                                 \
    Macro(PFNGLCREATETRANSFORMFEEDBACKSPROC, glCreateTransformFeedbacks);                       \
    Macro(PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC, glTransformFeedbackBufferBase);                 \
    Macro(PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC, glTransformFeedbackBufferRange);               \
    Macro(PFNGLGETTRANSFORMFEEDBACKIVPROC, glGetTransformFeedbackiv);                           \
    Macro(PFNGLGETTRANSFORMFEEDBACKI_VPROC, glGetTransformFeedbacki_v);                         \
    Macro(PFNGLGETTRANSFORMFEEDBACKI64_VPROC, glGetTransformFeedbacki64_v);                     \
    Macro(PFNGLCREATEBUFFERSPROC, glCreateBuffers);                                             \
    Macro(PFNGLNAMEDBUFFERSTORAGEPROC, glNamedBufferStorage);                                   \
    Macro(PFNGLNAMEDBUFFERDATAPROC, glNamedBufferData);                                         \
    Macro(PFNGLNAMEDBUFFERSUBDATAPROC, glNamedBufferSubData);                                   \
    Macro(PFNGLCOPYNAMEDBUFFERSUBDATAPROC, glCopyNamedBufferSubData);                           \
    Macro(PFNGLCLEARNAMEDBUFFERDATAPROC, glClearNamedBufferData);                               \
    Macro(PFNGLCLEARNAMEDBUFFERSUBDATAPROC, glClearNamedBufferSubData);                         \
    Macro(PFNGLMAPNAMEDBUFFERPROC, glMapNamedBuffer);                                           \
    Macro(PFNGLMAPNAMEDBUFFERRANGEPROC, glMapNamedBufferRange);                                 \
    Macro(PFNGLUNMAPNAMEDBUFFERPROC, glUnmapNamedBuffer);                                       \
    Macro(PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC, glFlushMappedNamedBufferRange);                 \
    Macro(PFNGLGETNAMEDBUFFERPARAMETERIVPROC, glGetNamedBufferParameteriv);                     \
    Macro(PFNGLGETNAMEDBUFFERPARAMETERI64VPROC, glGetNamedBufferParameteri64v);                 \
    Macro(PFNGLGETNAMEDBUFFERPOINTERVPROC, glGetNamedBufferPointerv);                           \
    Macro(PFNGLGETNAMEDBUFFERSUBDATAPROC, glGetNamedBufferSubData);                             \
    Macro(PFNGLCREATEFRAMEBUFFERSPROC, glCreateFramebuffers);                                   \
    Macro(PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC, glNamedFramebufferRenderbuffer);               \
    Macro(PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC, glNamedFramebufferParameteri);                   \
    Macro(PFNGLNAMEDFRAMEBUFFERTEXTUREPROC, glNamedFramebufferTexture);                         \
    Macro(PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC, glNamedFramebufferTextureLayer);               \
    Macro(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC, glNamedFramebufferDrawBuffer);                   \
    Macro(PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC, glNamedFramebufferDrawBuffers);                 \
    Macro(PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC, glNamedFramebufferReadBuffer);                   \
    Macro(PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC, glInvalidateNamedFramebufferData);           \
    Macro(PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC, glInvalidateNamedFramebufferSubData);     \
    Macro(PFNGLCLEARNAMEDFRAMEBUFFERIVPROC, glClearNamedFramebufferiv);                         \
    Macro(PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC, glClearNamedFramebufferuiv);                       \
    Macro(PFNGLCLEARNAMEDFRAMEBUFFERFVPROC, glClearNamedFramebufferfv);                         \
    Macro(PFNGLCLEARNAMEDFRAMEBUFFERFIPROC, glClearNamedFramebufferfi);                         \
    Macro(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer);                               \
    Macro(PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC, glCheckNamedFramebufferStatus);                 \
    Macro(PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC, glGetNamedFramebufferParameteriv);           \
    Macro(PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC,                                    \
          glGetNamedFramebufferAttachmentParameteriv);                                          \
    Macro(PFNGLCREATERENDERBUFFERSPROC, glCreateRenderbuffers);                                 \
    Macro(PFNGLNAMEDRENDERBUFFERSTORAGEPROC, glNamedRenderbufferStorage);                       \
    Macro(PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC, glNamedRenderbufferStorageMultisample); \
    Macro(PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC, glGetNamedRenderbufferParameteriv);         \
    Macro(PFNGLCREATETEXTURESPROC, glCreateTextures);                                           \
    Macro(PFNGLTEXTUREBUFFERPROC, glTextureBuffer);                                             \
    Macro(PFNGLTEXTUREBUFFERRANGEPROC, glTextureBufferRange);                                   \
    Macro(PFNGLTEXTURESTORAGE1DPROC, glTextureStorage1D);                                       \
    Macro(PFNGLTEXTURESTORAGE2DPROC, glTextureStorage2D);                                       \
    Macro(PFNGLTEXTURESTORAGE3DPROC, glTextureStorage3D);                                       \
    Macro(PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC, glTextureStorage2DMultisample);                 \
    Macro(PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC, glTextureStorage3DMultisample);                 \
    Macro(PFNGLTEXTURESUBIMAGE1DPROC, glTextureSubImage1D);                                     \
    Macro(PFNGLTEXTURESUBIMAGE2DPROC, glTextureSubImage2D);                                     \
    Macro(PFNGLTEXTURESUBIMAGE3DPROC, glTextureSubImage3D);                                     \
    Macro(PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC, glCompressedTextureSubImage1D);                 \
    Macro(PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC, glCompressedTextureSubImage2D);                 \
    Macro(PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC, glCompressedTextureSubImage3D);                 \
    Macro(PFNGLCOPYTEXTURESUBIMAGE1DPROC, glCopyTextureSubImage1D);                             \
    Macro(PFNGLCOPYTEXTURESUBIMAGE2DPROC, glCopyTextureSubImage2D);                             \
    Macro(PFNGLCOPYTEXTURESUBIMAGE3DPROC, glCopyTextureSubImage3D);                             \
    Macro(PFNGLTEXTUREPARAMETERFPROC, glTextureParameterf);                                     \
    Macro(PFNGLTEXTUREPARAMETERFVPROC, glTextureParameterfv);                                   \
    Macro(PFNGLTEXTUREPARAMETERIPROC, glTextureParameteri);                                     \
    Macro(PFNGLTEXTUREPARAMETERIIVPROC, glTextureParameterIiv);                                 \
    Macro(PFNGLTEXTUREPARAMETERIUIVPROC, glTextureParameterIuiv);                               \
    Macro(PFNGLTEXTUREPARAMETERIVPROC, glTextureParameteriv);                                   \
    Macro(PFNGLGENERATETEXTUREMIPMAPPROC, glGenerateTextureMipmap);                             \
    Macro(PFNGLBINDTEXTUREUNITPROC, glBindTextureUnit);                                         \
    Macro(PFNGLGETTEXTUREIMAGEPROC, glGetTextureImage);                                         \
    Macro(PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC, glGetCompressedTextureImage);                     \
    Macro(PFNGLGETTEXTURELEVELPARAMETERFVPROC, glGetTextureLevelParameterfv);                   \
    Macro(PFNGLGETTEXTURELEVELPARAMETERIVPROC, glGetTextureLevelParameteriv);                   \
    Macro(PFNGLGETTEXTUREPARAMETERFVPROC, glGetTextureParameterfv);                             \
    Macro(PFNGLGETTEXTUREPARAMETERIIVPROC, glGetTextureParameterIiv);                           \
    Macro(PFNGLGETTEXTUREPARAMETERIUIVPROC, glGetTextureParameterIuiv);                         \
    Macro(PFNGLGETTEXTUREPARAMETERIVPROC, glGetTextureParameteriv);                             \
    Macro(PFNGLCREATEVERTEXARRAYSPROC, glCreateVertexArrays);                                   \
    Macro(PFNGLDISABLEVERTEXARRAYATTRIBPROC, glDisableVertexArrayAttrib);                       \
    Macro(PFNGLENABLEVERTEXARRAYATTRIBPROC, glEnableVertexArrayAttrib);                         \
    Macro(PFNGLVERTEXARRAYELEMENTBUFFERPROC, glVertexArrayElementBuffer);                       \
    Macro(PFNGLVERTEXARRAYVERTEXBUFFERPROC, glVertexArrayVertexBuffer);                         \
    Macro(PFNGLVERTEXARRAYVERTEXBUFFERSPROC, glVertexArrayVertexBuffers);                       \
    Macro(PFNGLVERTEXARRAYATTRIBBINDINGPROC, glVertexArrayAttribBinding);                       \
    Macro(PFNGLVERTEXARRAYATTRIBFORMATPROC, glVertexArrayAttribFormat);                         \
    Macro(PFNGLVERTEXARRAYATTRIBIFORMATPROC, glVertexArrayAttribIFormat);                       \
    Macro(PFNGLVERTEXARRAYATTRIBLFORMATPROC, glVertexArrayAttribLFormat);                       \
    Macro(PFNGLVERTEXARRAYBINDINGDIVISORPROC, glVertexArrayBindingDivisor);                     \
    Macro(PFNGLGETVERTEXARRAYIVPROC, glGetVertexArrayiv);                                       \
    Macro(PFNGLGETVERTEXARRAYINDEXEDIVPROC, glGetVertexArrayIndexediv);                         \
    Macro(PFNGLGETVERTEXARRAYINDEXED64IVPROC, glGetVertexArrayIndexed64iv);                     \
    Macro(PFNGLCREATESAMPLERSPROC, glCreateSamplers);                                           \
    Macro(PFNGLCREATEPROGRAMPIPELINESPROC, glCreateProgramPipelines);                           \
    Macro(PFNGLCREATEQUERIESPROC, glCreateQueries);                                             \
    Macro(PFNGLGETQUERYBUFFEROBJECTI64VPROC, glGetQueryBufferObjecti64v);                       \
    Macro(PFNGLGETQUERYBUFFEROBJECTIVPROC, glGetQueryBufferObjectiv);                           \
    Macro(PFNGLGETQUERYBUFFEROBJECTUI64VPROC, glGetQueryBufferObjectui64v);                     \
    Macro(PFNGLGETQUERYBUFFEROBJECTUIVPROC, glGetQueryBufferObjectuiv);                         \
    Macro(PFNGLMEMORYBARRIERBYREGIONPROC, glMemoryBarrierByRegion);                             \
    Macro(PFNGLGETTEXTURESUBIMAGEPROC, glGetTextureSubImage);                                   \
    Macro(PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC, glGetCompressedTextureSubImage);               \
    Macro(PFNGLGETGRAPHICSRESETSTATUSPROC, glGetGraphicsResetStatus);                           \
    Macro(PFNGLGETNCOMPRESSEDTEXIMAGEPROC, glGetnCompressedTexImage);                           \
    Macro(PFNGLGETNTEXIMAGEPROC, glGetnTexImage);                                               \
    Macro(PFNGLGETNUNIFORMDVPROC, glGetnUniformdv);                                             \
    Macro(PFNGLGETNUNIFORMFVPROC, glGetnUniformfv);                                             \
    Macro(PFNGLGETNUNIFORMIVPROC, glGetnUniformiv);                                             \
    Macro(PFNGLGETNUNIFORMUIVPROC, glGetnUniformuiv);                                           \
    Macro(PFNGLREADNPIXELSPROC, glReadnPixels);                                                 \
    Macro(PFNGLTEXTUREBARRIERPROC, glTextureBarrier)

#define GL_4_6(Macro)                                                                 \
    Macro(PFNGLSPECIALIZESHADERPROC, glSpecializeShader);                             \
    Macro(PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC, glMultiDrawArraysIndirectCount);     \
    Macro(PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC, glMultiDrawElementsIndirectCount); \
    Macro(PFNGLPOLYGONOFFSETCLAMPPROC, glPolygonOffsetClamp)

// Macro must be defined by SOMETHING(Type, FuncName) as if
// Type FuncName; Could be the declaration of the pointer to
// function. Type is therefore a pointer to function type.
#define FOREACH_GL_ENTRYPOINTS(Macro) \
    GL_1_0(Macro)                     \
    GL_1_1(Macro)                     \
    GL_1_2(Macro)                     \
    GL_1_3(Macro)                     \
    GL_1_4(Macro)                     \
    GL_1_5(Macro)                     \
    GL_2_0(Macro)                     \
    GL_2_1(Macro)                     \
    GL_3_0(Macro)                     \
    GL_3_1(Macro)                     \
    GL_3_2(Macro)                     \
    GL_3_3(Macro)                     \
    GL_4_0(Macro)                     \
    GL_4_1(Macro)                     \
    GL_4_2(Macro)                     \
    GL_4_3(Macro)                     \
    GL_4_4(Macro)                     \
    GL_4_5(Macro)                     \
    GL_4_6(Macro)

#define DECLARE_GL_FUNCTIONS(Type, FuncName) extern Type RENDERER_GL_API FuncName;
FOREACH_GL_ENTRYPOINTS(DECLARE_GL_FUNCTIONS)
#undef DECLARE_GL_FUNCTIONS
