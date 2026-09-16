// Card Reader Enclosure reference — SZOMK AK-R-160 (118x75x22)
// OpenSCAD mockup for visual / 3D-print prototype
// Units: mm

outer_l = 118;
outer_w = 75;
outer_h = 22;
wall = 2.0;
fillet = 4;
bottom_h = 12;
top_h = outer_h - bottom_h;

// Card recess on lid outer surface
card_l = 86;
card_w = 54;
card_depth = 0.8;
card_r = 3;

// USB Type-C cutout on short edge
usb_w = 9.0;
usb_h = 3.5;
usb_z = 11.0; // center height from bottom — tune to PCB

module rounded_rect(l, w, h, r) {
  hull() {
    for (x = [-l/2+r, l/2-r])
      for (y = [-w/2+r, w/2-r])
        translate([x, y, 0]) cylinder(h=h, r=r, $fn=40);
  }
}

module bottom() {
  difference() {
    rounded_rect(outer_l, outer_w, bottom_h, fillet);
    translate([0, 0, wall])
      rounded_rect(outer_l-2*wall, outer_w-2*wall, bottom_h, max(1, fillet-1));
    // Type-C on +X short face
    translate([outer_l/2, 0, usb_z])
      cube([wall*3, usb_w, usb_h], center=true);
  }
}

module top() {
  difference() {
    rounded_rect(outer_l, outer_w, top_h, fillet);
    translate([0, 0, -0.1])
      rounded_rect(outer_l-2*wall, outer_w-2*wall, top_h-wall+0.2, max(1, fillet-1));
    // Card indentation on outer top
    translate([0, 0, top_h - card_depth])
      rounded_rect(card_l, card_w, card_depth+0.2, card_r);
    // LED holes
    translate([-outer_l/2+12, outer_w/2-10, 0])
      cylinder(h=top_h+1, r=1.5, $fn=24);
    translate([-outer_l/2+20, outer_w/2-10, 0])
      cylinder(h=top_h+1, r=1.5, $fn=24);
  }
}

translate([0, 0, 0]) bottom();
translate([0, 0, bottom_h + 0.3]) color([0.18,0.18,0.2]) top();

// bottom();
// top();
