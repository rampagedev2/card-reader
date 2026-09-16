// Card Reader Enclosure — Rev A
// Beautiful compact ABS shell for 70x90mm PCB
// Open in OpenSCAD → F6 → Export STL (top / bottom separately)
// Units: mm

/* [PCB] */
pcb_l = 90;
pcb_w = 70;
pcb_t = 1.6;

/* [Outer] */
wall = 1.8;
gap = 0.4;
fillet = 4;
outer_l = pcb_l + 2*wall + 4;   // ~97.6
outer_w = pcb_w + 2*wall + 4;   // ~77.6
outer_h = 18;
bottom_h = 8;
top_h = outer_h - bottom_h;

/* [RF window] */
rf_x = 18;
rf_y = 8;
rf_w = 45;
rf_l = 45;

module rounded_rect(l, w, h, r) {
  hull() {
    for (x = [-l/2+r, l/2-r])
      for (y = [-w/2+r, w/2-r])
        translate([x, y, 0]) cylinder(h=h, r=r, $fn=48);
  }
}

module bottom() {
  difference() {
    union() {
      // outer shell
      difference() {
        rounded_rect(outer_l, outer_w, bottom_h, fillet);
        translate([0,0,wall])
          rounded_rect(outer_l-2*wall, outer_w-2*wall, bottom_h, fillet-1);
      }
      // PCB standoffs
      for (x = [-pcb_l/2+3.5, pcb_l/2-3.5])
        for (y = [-pcb_w/2+3.5, pcb_w/2-3.5])
          translate([x, y, 0]) {
            cylinder(h=4.5, r=3.2, $fn=32);
            translate([0,0,4.5]) cylinder(h=1.2, r=1.1, $fn=24); // locating peg
          }
    }
    // USB-C cutout (short edge)
    translate([outer_l/2-1, 0, 4.2])
      cube([8, 10, 4], center=true);
    // screw bosses clearance
    for (x = [-outer_l/2+6, outer_l/2-6])
      for (y = [-outer_w/2+6, outer_w/2-6])
        translate([x, y, -0.1])
          cylinder(h=bottom_h+1, r=1.2, $fn=24);
  }
  // screw bosses
  for (x = [-outer_l/2+6, outer_l/2-6])
    for (y = [-outer_w/2+6, outer_w/2-6])
      difference() {
        translate([x, y, 0]) cylinder(h=bottom_h-0.5, r=3.5, $fn=32);
        translate([x, y, 1]) cylinder(h=bottom_h, r=1.1, $fn=24);
      }
}

module top() {
  difference() {
    union() {
      difference() {
        rounded_rect(outer_l, outer_w, top_h, fillet);
        translate([0,0,-0.1])
          rounded_rect(outer_l-2*wall, outer_w-2*wall, top_h-wall+0.2, fillet-1);
      }
      // lip for snap/fit
      translate([0,0,0])
        difference() {
          rounded_rect(outer_l-2*wall+1.2, outer_w-2*wall+1.2, 2.2, fillet-1);
          rounded_rect(outer_l-2*wall-0.6, outer_w-2*wall-0.6, 2.4, fillet-1.5);
        }
    }
    // recessed RF “tap zone” (thinned lid 0.9 mm)
    translate([-pcb_l/2+rf_x+rf_l/2-outer_l/2+outer_l/2,
               -pcb_w/2+rf_y+rf_w/2, top_h-0.95])
      rounded_rect(rf_l, rf_w, 1.2, 3);
    // aesthetic shallow recess ring
    translate([0, -8, top_h-0.4])
      difference() {
        rounded_rect(52, 52, 0.5, 4);
        rounded_rect(46, 46, 0.6, 3);
      }
    // LED light-pipe holes
    translate([-18, 28, 0]) cylinder(h=top_h+1, r=1.4, $fn=24);
    translate([-10, 28, 0]) cylinder(h=top_h+1, r=1.4, $fn=24);
    // brand recess (pad print)
    translate([0, 30, top_h-0.35])
      linear_extrude(0.5)
        text("CARD", size=5, halign="center", valign="center", font="Segoe UI:style=Bold");
  }
}

// Preview assembly
translate([0, 0, 0]) bottom();
translate([0, 0, bottom_h + 0.2]) color([0.15,0.15,0.17,0.92]) top();

// Uncomment to export single parts:
// bottom();
// top();
