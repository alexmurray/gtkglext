/*
 * 3-D gear wheels.  This program is in the public domain.
 *
 * Brian Paul
 */

/* Conversion to GLUT by Mark J. Kilgard */

/* Conversion to GtkGLExt by Naofumi Yasufuku */


#include <math.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkgl.h>

#include <GL/gl.h>
#include <GL/glu.h>

#ifndef M_PI
#define M_PI 3.14159265
#endif

static const gint config_attributes[] = {
  GDK_GL_DOUBLEBUFFER,
  GDK_GL_RGBA,
  GDK_GL_RED_SIZE,        1,
  GDK_GL_GREEN_SIZE,      1,
  GDK_GL_BLUE_SIZE,       1,
  GDK_GL_DEPTH_SIZE,      12,
  GDK_GL_ATTRIB_LIST_NONE
};

static GTimer *timer = NULL;
static gint Frames = 0;

/**

  Draw a gear wheel.  You'll probably want to call this function when
  building a display list since we do a lot of trig here.
 
  Input:  inner_radius - radius of hole at center
          outer_radius - radius at center of teeth
          width - width of gear
          teeth - number of teeth
          tooth_depth - depth of tooth

 **/

static void
gear(GLfloat inner_radius,
     GLfloat outer_radius,
     GLfloat width,
     GLint   teeth,
     GLfloat tooth_depth)
{
  GLint i;
  GLfloat r0, r1, r2;
  GLfloat angle, da;
  GLfloat u, v, len;

  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2.0;
  r2 = outer_radius + tooth_depth / 2.0;

  da = 2.0 * M_PI / teeth / 4.0;

  glShadeModel(GL_FLAT);

  glNormal3f(0.0, 0.0, 1.0);

  /* draw front face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    if (i < teeth) {
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    }
  }
  glEnd();

  /* draw front sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
  }
  glEnd();

  glNormal3f(0.0, 0.0, -1.0);

  /* draw back face */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    if (i < teeth) {
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    }
  }
  glEnd();

  /* draw back sides of teeth */
  glBegin(GL_QUADS);
  da = 2.0 * M_PI / teeth / 4.0;
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
  }
  glEnd();

  /* draw outward faces of teeth */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i < teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;

    glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
    glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
    u = r2 * cos(angle + da) - r1 * cos(angle);
    v = r2 * sin(angle + da) - r1 * sin(angle);
    len = sqrt(u * u + v * v);
    u /= len;
    v /= len;
    glNormal3f(v, -u, 0.0);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
    glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), width * 0.5);
    glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), -width * 0.5);
    u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
    v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
    glNormal3f(v, -u, 0.0);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), width * 0.5);
    glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), -width * 0.5);
    glNormal3f(cos(angle), sin(angle), 0.0);
  }

  glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
  glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

  glEnd();

  glShadeModel(GL_SMOOTH);

  /* draw inside radius cylinder */
  glBegin(GL_QUAD_STRIP);
  for (i = 0; i <= teeth; i++) {
    angle = i * 2.0 * M_PI / teeth;
    glNormal3f(-cos(angle), -sin(angle), 0.0);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
    glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
  }
  glEnd();

}

static GLfloat view_rotx = 20.0, view_roty = 30.0, view_rotz = 0.0;
static GLint gear1, gear2, gear3;
static GLfloat angle = 0.0;

static gboolean
draw(GtkWidget      *widget,
     GdkEventExpose *event,
     gpointer        data)
{
  /* OpenGL begin. */
  gtk_widget_gl_begin(widget);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    glRotatef(view_rotz, 0.0, 0.0, 1.0);

    glPushMatrix();
      glTranslatef(-3.0, -2.0, 0.0);
      glRotatef(angle, 0.0, 0.0, 1.0);
      glCallList(gear1);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(3.1, -2.0, 0.0);
      glRotatef(-2.0 * angle - 9.0, 0.0, 0.0, 1.0);
      glCallList(gear2);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-3.1, 4.2, 0.0);
      glRotatef(-2.0 * angle - 25.0, 0.0, 0.0, 1.0);
      glCallList(gear3);
    glPopMatrix();

  glPopMatrix();

  if (gtk_widget_gl_is_double_buffer(widget))
    gtk_widget_gl_swap_buffers(widget);
  else
    glFlush();

  gtk_widget_gl_end(widget);
  /* OpenGL end. */

  Frames++;

  {
     gdouble seconds = g_timer_elapsed(timer, NULL);
     if (seconds >= 5.0) {
        gdouble fps = Frames / seconds;
        g_print("%d frames in %6.3f seconds = %6.3f FPS\n", Frames, seconds, fps);
        g_timer_reset(timer);
        Frames = 0;
     }
  }

  return TRUE;
}

static gboolean
idle(GtkWidget *widget)
{
  GdkRectangle area;

  angle += 2.0;

  area.x = 0;
  area.y = 0;
  area.width  = widget->allocation.width;
  area.height = widget->allocation.height;

  gtk_widget_draw(widget, &area);

  return TRUE;
}

/* change view angle, exit upon ESC */
/* ARGSUSED1 */
static gboolean
key(GtkWidget   *widget,
    GdkEventKey *event,
    gpointer     data)
{
  GdkRectangle area;

  switch (event->keyval) {
  case GDK_z:
    view_rotz += 5.0;
    break;
  case GDK_Z:
    view_rotz -= 5.0;
    break;
  case GDK_Up:
    view_rotx += 5.0;
    break;
  case GDK_Down:
    view_rotx -= 5.0;
    break;
  case GDK_Left:
    view_roty += 5.0;
    break;
  case GDK_Right:
    view_roty -= 5.0;
    break;
  case GDK_Escape:
    gtk_main_quit();
    break;
  default:
    return TRUE;
  }

  area.x = 0;
  area.y = 0;
  area.width  = widget->allocation.width;
  area.height = widget->allocation.height;

  gtk_widget_draw(widget, &area);

  return TRUE;
}

/* new window size or exposure */
static gboolean
reshape(GtkWidget         *widget,
        GdkEventConfigure *event,
        gpointer           data)
{
  GLfloat h = (GLfloat) (widget->allocation.height) / (GLfloat) (widget->allocation.width);

  /* OpenGL begin. */
  gtk_widget_gl_begin(widget);

  glViewport(0, 0, widget->allocation.width, widget->allocation.height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -40.0);

  gtk_widget_gl_end(widget);
  /* OpenGL end. */

  return TRUE;
}

static void
init(GtkWidget *widget,
     gpointer   data)
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};
  static GLfloat red[4] = {0.8, 0.1, 0.0, 1.0};
  static GLfloat green[4] = {0.0, 0.8, 0.2, 1.0};
  static GLfloat blue[4] = {0.2, 0.2, 1.0, 1.0};

  /* OpenGL begin. */
  gtk_widget_gl_begin(widget);

  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  /* make the gears */
  gear1 = glGenLists(1);
  glNewList(gear1, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
  gear(1.0, 4.0, 1.0, 20, 0.7);
  glEndList();

  gear2 = glGenLists(1);
  glNewList(gear2, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
  gear(0.5, 2.0, 2.0, 10, 0.7);
  glEndList();

  gear3 = glGenLists(1);
  glNewList(gear3, GL_COMPILE);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
  gear(1.3, 2.0, 0.5, 10, 0.7);
  glEndList();

  glEnable(GL_NORMALIZE);

  g_print("\n");
  g_print("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
  g_print("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
  g_print("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
  g_print("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
  g_print("\n");

  gtk_widget_gl_end(widget);
  /* OpenGL end. */
}

static gboolean
visible(GtkWidget          *widget,
        GdkEventVisibility *event,
        gpointer            data)
{
  static guint id = 0;

  if (event->state == GDK_VISIBILITY_FULLY_OBSCURED) {
    if (id != 0) {
      gtk_idle_remove (id);
      id = 0;
    }
  } else {
    if (id == 0)
      id = gtk_idle_add((GtkFunction) idle, widget);
  }

  return TRUE;
}

static gint
quit(GtkWidget *widget,
     GdkEvent  *event,
     gpointer   data)
{
  gtk_main_quit();

  return FALSE;
}

int
main(int   argc,
     char *argv[])
{
  GdkGLConfig *glconfig;
  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *drawing_area;
  GtkWidget *button;

  /*
   * Init
   */

  gtk_init(&argc, &argv);

  /*
   * OpenGL extension is supported?
   */

  if (!gdk_gl_query_extension())
    {
      g_print("\n*** OpenGL extension is not supported\n");
      gtk_exit(1);
    }

  /*
   * Configure OpenGL-capable visual.
   */

  /* Try double buffered visual */
  glconfig = gdk_gl_config_new(&config_attributes[0]);
  if (glconfig == NULL)
    {
      g_print("*** Cannot find the OpenGL-capable visual with double buffering support.\n");
      g_print("*** Trying single buffering visual.\n");

      /* Try single buffered visual */
      glconfig = gdk_gl_config_new(&config_attributes[1]);
      if (glconfig == NULL)
        {
          g_print("*** Cannot find an OpenGL-capable visual\n");
          gtk_exit(1);
        }
    }

  /*
   * Top-level window.
   */

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(window, "Gears");

  g_signal_connect(G_OBJECT(window), "delete_event",
                   G_CALLBACK(quit), NULL);
  g_signal_connect(G_OBJECT(window), "key_press_event",
                   G_CALLBACK(key), NULL);  

  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show(vbox);

  /*
   * Drawing area for drawing OpenGL scene.
   */

  drawing_area = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area, 300, 300);

  /* Set OpenGL-capability to the widget. */
  gtk_widget_set_gl_capability(drawing_area,
                               glconfig,
                               GDK_GL_RGBA_TYPE,
                               NULL,
                               TRUE);

  gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);

  gtk_widget_set_events(drawing_area,
                        GDK_EXPOSURE_MASK |
                        GDK_BUTTON_PRESS_MASK |
                        GDK_VISIBILITY_NOTIFY_MASK);

  g_signal_connect(G_OBJECT(drawing_area), "realize",
		   G_CALLBACK(init), NULL);
  g_signal_connect(G_OBJECT(drawing_area), "configure_event",
                   G_CALLBACK(reshape), NULL);
  g_signal_connect(G_OBJECT(drawing_area), "expose_event",
                   G_CALLBACK(draw), NULL);
  g_signal_connect(G_OBJECT(drawing_area), "visibility_notify_event",
                   G_CALLBACK(visible), NULL);

  gtk_widget_show(drawing_area);

  /*
   * Simple quit button.
   */

  button = gtk_button_new_with_label("Quit");
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(button), "clicked",
                   G_CALLBACK(quit), NULL);

  gtk_widget_show(button);

  /*
   * Show window.
   */

  gtk_widget_show(window);

  /*
   * Main loop.
   */

  timer = g_timer_new();
  g_timer_start(timer);

  gtk_main();

  return 0;
}