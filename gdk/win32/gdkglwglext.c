/* GdkGLExt - OpenGL Extension to GDK
 * Copyright (C) 2002-2003  Naofumi Yasufuku
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA.
 */

#include "gdkglwin32.h"
#include "gdkglprivate-win32.h"
#include "gdkglwglext.h"

#define _GDK_GL_PROCS(__ext_name) \
  _GDK_GL_CONCAT (_proc_, __ext_name)

#define _GDK_GL_PROC_TYPE(__proc_name) \
  _GDK_GL_CONCAT (GdkGLProc_, __proc_name)

#define _GDK_GL_GET_PROC(__procs, __proc_name)                                          \
GdkGLProc                                                                               \
_GDK_GL_CONCAT (gdk_gl_get_, __proc_name) (void)                                        \
{                                                                                       \
  if (wglGetCurrentContext () == NULL)                                                  \
    return NULL;                                                                        \
                                                                                        \
  if (__procs.__proc_name == (_GDK_GL_PROC_TYPE(__proc_name)) -1)                       \
    {                                                                                   \
      __procs.__proc_name =                                                             \
        (_GDK_GL_PROC_TYPE (__proc_name)) gdk_gl_get_proc_address (#__proc_name);       \
                                                                                        \
      GDK_GL_NOTE (MISC,                                                                \
                   g_message (" - gdk_gl_get_%s () - %s",                               \
                              #__proc_name,                                             \
                              (__procs.__proc_name) ? "supported" : "not supported"));  \
    }                                                                                   \
                                                                                        \
  return (GdkGLProc) (__procs.__proc_name);                                             \
}

/* 
 * WGL_ARB_buffer_region
 */

static GdkGL_WGL_ARB_buffer_region _GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region), wglCreateBufferRegionARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region), wglDeleteBufferRegionARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region), wglSaveBufferRegionARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region), wglRestoreBufferRegionARB)

GdkGL_WGL_ARB_buffer_region *
gdk_gl_get_WGL_ARB_buffer_region (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_buffer_region ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_buffer_region");

      if (supported)
        {
          supported &= (gdk_gl_get_wglCreateBufferRegionARB ()  != NULL);
          supported &= (gdk_gl_get_wglDeleteBufferRegionARB ()  != NULL);
          supported &= (gdk_gl_get_wglSaveBufferRegionARB ()    != NULL);
          supported &= (gdk_gl_get_wglRestoreBufferRegionARB () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_buffer_region));
}

/* 
 * WGL_ARB_extensions_string
 */

static GdkGL_WGL_ARB_extensions_string _GDK_GL_PROCS (GdkGL_WGL_ARB_extensions_string) = {
  (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_extensions_string), wglGetExtensionsStringARB)

GdkGL_WGL_ARB_extensions_string *
gdk_gl_get_WGL_ARB_extensions_string (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_extensions_string ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_extensions_string");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetExtensionsStringARB () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_extensions_string));
}

/* 
 * WGL_ARB_pixel_format
 */

static GdkGL_WGL_ARB_pixel_format _GDK_GL_PROCS (GdkGL_WGL_ARB_pixel_format) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pixel_format), wglGetPixelFormatAttribivARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pixel_format), wglGetPixelFormatAttribfvARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pixel_format), wglChoosePixelFormatARB)

GdkGL_WGL_ARB_pixel_format *
gdk_gl_get_WGL_ARB_pixel_format (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_pixel_format ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_pixel_format");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetPixelFormatAttribivARB () != NULL);
          supported &= (gdk_gl_get_wglGetPixelFormatAttribfvARB () != NULL);
          supported &= (gdk_gl_get_wglChoosePixelFormatARB ()      != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_pixel_format));
}

/* 
 * WGL_ARB_make_current_read
 */

static GdkGL_WGL_ARB_make_current_read _GDK_GL_PROCS (GdkGL_WGL_ARB_make_current_read) = {
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_make_current_read), wglMakeContextCurrentARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_make_current_read), wglGetCurrentReadDCARB)

GdkGL_WGL_ARB_make_current_read *
gdk_gl_get_WGL_ARB_make_current_read (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_make_current_read ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_make_current_read");

      if (supported)
        {
          supported &= (gdk_gl_get_wglMakeContextCurrentARB () != NULL);
          supported &= (gdk_gl_get_wglGetCurrentReadDCARB ()   != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_make_current_read));
}

/* 
 * WGL_ARB_pbuffer
 */

static GdkGL_WGL_ARB_pbuffer _GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer), wglCreatePbufferARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer), wglGetPbufferDCARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer), wglReleasePbufferDCARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer), wglDestroyPbufferARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer), wglQueryPbufferARB)

GdkGL_WGL_ARB_pbuffer *
gdk_gl_get_WGL_ARB_pbuffer (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_pbuffer ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_pbuffer");

      if (supported)
        {
          supported &= (gdk_gl_get_wglCreatePbufferARB ()    != NULL);
          supported &= (gdk_gl_get_wglGetPbufferDCARB ()     != NULL);
          supported &= (gdk_gl_get_wglReleasePbufferDCARB () != NULL);
          supported &= (gdk_gl_get_wglDestroyPbufferARB ()   != NULL);
          supported &= (gdk_gl_get_wglQueryPbufferARB ()     != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_pbuffer));
}

/* 
 * WGL_ARB_render_texture
 */

static GdkGL_WGL_ARB_render_texture _GDK_GL_PROCS (GdkGL_WGL_ARB_render_texture) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_render_texture), wglBindTexImageARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_render_texture), wglReleaseTexImageARB)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_ARB_render_texture), wglSetPbufferAttribARB)

GdkGL_WGL_ARB_render_texture *
gdk_gl_get_WGL_ARB_render_texture (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_ARB_render_texture ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_ARB_render_texture");

      if (supported)
        {
          supported &= (gdk_gl_get_wglBindTexImageARB ()     != NULL);
          supported &= (gdk_gl_get_wglReleaseTexImageARB ()  != NULL);
          supported &= (gdk_gl_get_wglSetPbufferAttribARB () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_ARB_render_texture));
}

/* 
 * WGL_EXT_display_color_table
 */

static GdkGL_WGL_EXT_display_color_table _GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table), wglCreateDisplayColorTableEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table), wglLoadDisplayColorTableEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table), wglBindDisplayColorTableEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table), wglDestroyDisplayColorTableEXT)

GdkGL_WGL_EXT_display_color_table *
gdk_gl_get_WGL_EXT_display_color_table (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_display_color_table ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_display_color_table");

      if (supported)
        {
          supported &= (gdk_gl_get_wglCreateDisplayColorTableEXT ()  != NULL);
          supported &= (gdk_gl_get_wglLoadDisplayColorTableEXT ()    != NULL);
          supported &= (gdk_gl_get_wglBindDisplayColorTableEXT ()    != NULL);
          supported &= (gdk_gl_get_wglDestroyDisplayColorTableEXT () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_display_color_table));
}

/* 
 * WGL_EXT_extensions_string
 */

static GdkGL_WGL_EXT_extensions_string _GDK_GL_PROCS (GdkGL_WGL_EXT_extensions_string) = {
  (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_extensions_string), wglGetExtensionsStringEXT)

GdkGL_WGL_EXT_extensions_string *
gdk_gl_get_WGL_EXT_extensions_string (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_extensions_string ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_extensions_string");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetExtensionsStringEXT () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_extensions_string));
}

/* 
 * WGL_EXT_make_current_read
 */

static GdkGL_WGL_EXT_make_current_read _GDK_GL_PROCS (GdkGL_WGL_EXT_make_current_read) = {
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_make_current_read), wglMakeContextCurrentEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_make_current_read), wglGetCurrentReadDCEXT)

GdkGL_WGL_EXT_make_current_read *
gdk_gl_get_WGL_EXT_make_current_read (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_make_current_read ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_make_current_read");

      if (supported)
        {
          supported &= (gdk_gl_get_wglMakeContextCurrentEXT () != NULL);
          supported &= (gdk_gl_get_wglGetCurrentReadDCEXT ()   != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_make_current_read));
}

/* 
 * WGL_EXT_pbuffer
 */

static GdkGL_WGL_EXT_pbuffer _GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer), wglCreatePbufferEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer), wglGetPbufferDCEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer), wglReleasePbufferDCEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer), wglDestroyPbufferEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer), wglQueryPbufferEXT)

GdkGL_WGL_EXT_pbuffer *
gdk_gl_get_WGL_EXT_pbuffer (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_pbuffer ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_pbuffer");

      if (supported)
        {
          supported &= (gdk_gl_get_wglCreatePbufferEXT ()    != NULL);
          supported &= (gdk_gl_get_wglGetPbufferDCEXT ()     != NULL);
          supported &= (gdk_gl_get_wglReleasePbufferDCEXT () != NULL);
          supported &= (gdk_gl_get_wglDestroyPbufferEXT ()   != NULL);
          supported &= (gdk_gl_get_wglQueryPbufferEXT ()     != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_pbuffer));
}

/* 
 * WGL_EXT_pixel_format
 */

static GdkGL_WGL_EXT_pixel_format _GDK_GL_PROCS (GdkGL_WGL_EXT_pixel_format) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pixel_format), wglGetPixelFormatAttribivEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pixel_format), wglGetPixelFormatAttribfvEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_pixel_format), wglChoosePixelFormatEXT)

GdkGL_WGL_EXT_pixel_format *
gdk_gl_get_WGL_EXT_pixel_format (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_pixel_format ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_pixel_format");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetPixelFormatAttribivEXT () != NULL);
          supported &= (gdk_gl_get_wglGetPixelFormatAttribfvEXT () != NULL);
          supported &= (gdk_gl_get_wglChoosePixelFormatEXT ()      != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_pixel_format));
}

/* 
 * WGL_EXT_swap_control
 */

static GdkGL_WGL_EXT_swap_control _GDK_GL_PROCS (GdkGL_WGL_EXT_swap_control) = {
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_swap_control), wglSwapIntervalEXT)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_EXT_swap_control), wglGetSwapIntervalEXT)

GdkGL_WGL_EXT_swap_control *
gdk_gl_get_WGL_EXT_swap_control (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_EXT_swap_control ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_EXT_swap_control");

      if (supported)
        {
          supported &= (gdk_gl_get_wglSwapIntervalEXT ()    != NULL);
          supported &= (gdk_gl_get_wglGetSwapIntervalEXT () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_EXT_swap_control));
}

/* 
 * WGL_NV_vertex_array_range
 */

static GdkGL_WGL_NV_vertex_array_range _GDK_GL_PROCS (GdkGL_WGL_NV_vertex_array_range) = {
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_NV_vertex_array_range), wglAllocateMemoryNV)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_NV_vertex_array_range), wglFreeMemoryNV)

GdkGL_WGL_NV_vertex_array_range *
gdk_gl_get_WGL_NV_vertex_array_range (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_NV_vertex_array_range ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_NV_vertex_array_range");

      if (supported)
        {
          supported &= (gdk_gl_get_wglAllocateMemoryNV () != NULL);
          supported &= (gdk_gl_get_wglFreeMemoryNV ()     != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_NV_vertex_array_range));
}

/* 
 * WGL_OML_sync_control
 */

static GdkGL_WGL_OML_sync_control _GDK_GL_PROCS (GdkGL_WGL_OML_sync_control) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1,
  (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglGetSyncValuesOML)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglGetMscRateOML)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglSwapBuffersMscOML)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglSwapLayerBuffersMscOML)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglWaitForMscOML)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control), wglWaitForSbcOML)

GdkGL_WGL_OML_sync_control *
gdk_gl_get_WGL_OML_sync_control (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_OML_sync_control ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_OML_sync_control");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetSyncValuesOML ()       != NULL);
          supported &= (gdk_gl_get_wglGetMscRateOML ()          != NULL);
          supported &= (gdk_gl_get_wglSwapBuffersMscOML ()      != NULL);
          supported &= (gdk_gl_get_wglSwapLayerBuffersMscOML () != NULL);
          supported &= (gdk_gl_get_wglWaitForMscOML ()          != NULL);
          supported &= (gdk_gl_get_wglWaitForSbcOML ()          != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_OML_sync_control));
}

/* 
 * WGL_I3D_digital_video_control
 */

static GdkGL_WGL_I3D_digital_video_control _GDK_GL_PROCS (GdkGL_WGL_I3D_digital_video_control) = {
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_digital_video_control), wglGetDigitalVideoParametersI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_digital_video_control), wglSetDigitalVideoParametersI3D)

GdkGL_WGL_I3D_digital_video_control *
gdk_gl_get_WGL_I3D_digital_video_control (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_digital_video_control ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_digital_video_control");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetDigitalVideoParametersI3D () != NULL);
          supported &= (gdk_gl_get_wglSetDigitalVideoParametersI3D () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_digital_video_control));
}

/* 
 * WGL_I3D_gamma
 */

static GdkGL_WGL_I3D_gamma _GDK_GL_PROCS (GdkGL_WGL_I3D_gamma) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_gamma), wglGetGammaTableParametersI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_gamma), wglSetGammaTableParametersI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_gamma), wglGetGammaTableI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_gamma), wglSetGammaTableI3D)

GdkGL_WGL_I3D_gamma *
gdk_gl_get_WGL_I3D_gamma (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_gamma ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_gamma");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetGammaTableParametersI3D () != NULL);
          supported &= (gdk_gl_get_wglSetGammaTableParametersI3D () != NULL);
          supported &= (gdk_gl_get_wglGetGammaTableI3D ()           != NULL);
          supported &= (gdk_gl_get_wglSetGammaTableI3D ()           != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_gamma));
}

/* 
 * WGL_I3D_genlock
 */

static GdkGL_WGL_I3D_genlock _GDK_GL_PROCS (GdkGL_WGL_I3D_genlock) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1,
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1,
  (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglEnableGenlockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglDisableGenlockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglIsEnabledGenlockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGenlockSourceI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGetGenlockSourceI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGenlockSourceEdgeI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGetGenlockSourceEdgeI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGenlockSampleRateI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGetGenlockSampleRateI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGenlockSourceDelayI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglGetGenlockSourceDelayI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock), wglQueryGenlockMaxSourceDelayI3D)

GdkGL_WGL_I3D_genlock *
gdk_gl_get_WGL_I3D_genlock (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_genlock ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_genlock");

      if (supported)
        {
          supported &= (gdk_gl_get_wglEnableGenlockI3D ()              != NULL);
          supported &= (gdk_gl_get_wglDisableGenlockI3D ()             != NULL);
          supported &= (gdk_gl_get_wglIsEnabledGenlockI3D ()           != NULL);
          supported &= (gdk_gl_get_wglGenlockSourceI3D ()              != NULL);
          supported &= (gdk_gl_get_wglGetGenlockSourceI3D ()           != NULL);
          supported &= (gdk_gl_get_wglGenlockSourceEdgeI3D ()          != NULL);
          supported &= (gdk_gl_get_wglGetGenlockSourceEdgeI3D ()       != NULL);
          supported &= (gdk_gl_get_wglGenlockSampleRateI3D ()          != NULL);
          supported &= (gdk_gl_get_wglGetGenlockSampleRateI3D ()       != NULL);
          supported &= (gdk_gl_get_wglGenlockSourceDelayI3D ()         != NULL);
          supported &= (gdk_gl_get_wglGetGenlockSourceDelayI3D ()      != NULL);
          supported &= (gdk_gl_get_wglQueryGenlockMaxSourceDelayI3D () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_genlock));
}

/* 
 * WGL_I3D_image_buffer
 */

static GdkGL_WGL_I3D_image_buffer _GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer), wglCreateImageBufferI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer), wglDestroyImageBufferI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer), wglAssociateImageBufferEventsI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer), wglReleaseImageBufferEventsI3D)

GdkGL_WGL_I3D_image_buffer *
gdk_gl_get_WGL_I3D_image_buffer (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_image_buffer ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_image_buffer");

      if (supported)
        {
          supported &= (gdk_gl_get_wglCreateImageBufferI3D ()          != NULL);
          supported &= (gdk_gl_get_wglDestroyImageBufferI3D ()         != NULL);
          supported &= (gdk_gl_get_wglAssociateImageBufferEventsI3D () != NULL);
          supported &= (gdk_gl_get_wglReleaseImageBufferEventsI3D ()   != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_image_buffer));
}

/* 
 * WGL_I3D_swap_frame_lock
 */

static GdkGL_WGL_I3D_swap_frame_lock _GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock), wglEnableFrameLockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock), wglDisableFrameLockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock), wglIsEnabledFrameLockI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock), wglQueryFrameLockMasterI3D)

GdkGL_WGL_I3D_swap_frame_lock *
gdk_gl_get_WGL_I3D_swap_frame_lock (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_swap_frame_lock ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_swap_frame_lock");

      if (supported)
        {
          supported &= (gdk_gl_get_wglEnableFrameLockI3D ()      != NULL);
          supported &= (gdk_gl_get_wglDisableFrameLockI3D ()     != NULL);
          supported &= (gdk_gl_get_wglIsEnabledFrameLockI3D ()   != NULL);
          supported &= (gdk_gl_get_wglQueryFrameLockMasterI3D () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_lock));
}

/* 
 * WGL_I3D_swap_frame_usage
 */

static GdkGL_WGL_I3D_swap_frame_usage _GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage) = {
  (gpointer) -1, (gpointer) -1, (gpointer) -1, (gpointer) -1
};

_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage), wglGetFrameUsageI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage), wglBeginFrameTrackingI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage), wglEndFrameTrackingI3D)
_GDK_GL_GET_PROC (_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage), wglQueryFrameTrackingI3D)

GdkGL_WGL_I3D_swap_frame_usage *
gdk_gl_get_WGL_I3D_swap_frame_usage (GdkGLConfig *glconfig)
{
  static gint supported = -1;

  GDK_GL_NOTE (FUNC, g_message (" - gdk_gl_get_WGL_I3D_swap_frame_usage ()"));

  if (wglGetCurrentContext () == NULL)
    return NULL;

  if (supported == -1)
    {
      supported = gdk_win32_gl_query_wgl_extension (glconfig, "WGL_I3D_swap_frame_usage");

      if (supported)
        {
          supported &= (gdk_gl_get_wglGetFrameUsageI3D ()      != NULL);
          supported &= (gdk_gl_get_wglBeginFrameTrackingI3D () != NULL);
          supported &= (gdk_gl_get_wglEndFrameTrackingI3D ()   != NULL);
          supported &= (gdk_gl_get_wglQueryFrameTrackingI3D () != NULL);
        }
    }

  if (!supported)
    return NULL;

  return &(_GDK_GL_PROCS (GdkGL_WGL_I3D_swap_frame_usage));
}
