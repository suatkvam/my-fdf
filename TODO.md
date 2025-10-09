# FDF 3D Format Support - TODO List

## 📋 **Development Roadmap**

### **🎯 Priority 1: Binary File Reader**
- [ ] Create `format/binary_reader.c`
  - [ ] `read_uint8()` - Read single byte
  - [ ] `read_uint16_le()` - Read 16-bit little endian
  - [ ] `read_uint32_le()` - Read 32-bit little endian
  - [ ] `read_float_le()` - Read float little endian (for STL files)
  - [ ] `read_binary_chunk()` - Read bulk data
  - [ ] Error handling for file I/O

### **🎯 Priority 2: STL File Loader**
- [ ] Create `format/stl_loader.c`
  - [ ] `load_stl_binary()` - Binary STL format parser
  - [ ] `load_stl_ascii()` - ASCII STL format parser  
  - [ ] `parse_stl_header()` - File format detection (binary vs ASCII)
  - [ ] `stl_to_mesh()` - Convert STL data to t_mesh structure
  - [ ] Triangle extraction and normal calculation
  - [ ] Memory management for large STL files

### **🎯 Priority 3: Image Format Support**
- [ ] Create `format/image_reader.c`
  - [ ] `load_ppm_image()` - Simple PPM format (no external libs needed)
  - [ ] `load_pgm_image()` - Grayscale PGM format
  - [ ] `detect_image_format()` - Auto-detect format by header
  - [ ] `validate_image_data()` - Check image integrity
  - [ ] Support for P3 (ASCII) and P6 (binary) PPM variants

### **🎯 Priority 4: Image to Height Map Conversion**
- [ ] Create `format/heightmap_converter.c`
  - [ ] `image_to_heightmap()` - Convert pixel brightness to Z values
  - [ ] `save_fdf_from_image()` - Export converted data as .fdf file
  - [ ] `calculate_height_scale()` - Auto-scale Z values based on image size
  - [ ] `rgb_to_grayscale()` - Convert color images to height data
  - [ ] Color preservation for visualization

### **🎯 Priority 5: OBJ File Loader**
- [ ] Create `format/obj_loader.c`
  - [ ] `parse_obj_vertex()` - Parse "v x y z" vertex lines
  - [ ] `parse_obj_face()` - Parse "f v1 v2 v3" triangle faces
  - [ ] `parse_obj_normal()` - Parse "vn x y z" normal vectors
  - [ ] `obj_to_mesh()` - Full OBJ to mesh conversion
  - [ ] Handle complex OBJ features (groups, materials, textures)
  - [ ] Triangulation for quad faces

### **🎯 Priority 6: Format Detection System**
- [ ] Create `format/format_detector.c`
  - [ ] `detect_file_format()` - Auto-detect by extension and header
  - [ ] `is_binary_stl()` - Check STL binary signature
  - [ ] `is_ascii_stl()` - Check for "solid" keyword
  - [ ] `is_image_file()` - Detect PPM/PGM/PNG/JPG
  - [ ] `is_obj_file()` - Detect Wavefront OBJ format
  - [ ] `get_file_extension()` - Extract file extension

### **🎯 Priority 7: Main Integration**
- [ ] Update `main.c`
  - [ ] Multi-format file support
  - [ ] Auto-detect and load appropriate format
  - [ ] Convert all formats to unified t_mesh
  - [ ] Command line options for format specification
  - [ ] Error handling for unsupported formats

### **🛠️ Build System Updates**
- [ ] Update `Makefile`
  ```makefile
  FORMAT_SRC= binary_reader.c stl_loader.c image_reader.c \
              heightmap_converter.c obj_loader.c format_detector.c
  ```
  - [ ] Add `$(addprefix format/, $(FORMAT_SRC))` to SRCS
  - [ ] Update dependencies

### **🧪 Testing & Validation**
- [ ] Create test files
  - [ ] Sample STL files (binary and ASCII)
  - [ ] Test PPM/PGM images
  - [ ] Simple OBJ models
  - [ ] Validation scripts

### **📖 Documentation**
- [ ] Update README with supported formats
- [ ] Add usage examples for each format
- [ ] Document conversion workflows
- [ ] Performance benchmarks

## **🎮 Advanced Features (Future)**
- [ ] PLY format support
- [ ] PNG/JPG support with external libraries
- [ ] Texture mapping for OBJ files
- [ ] Animation support (multiple frames)
- [ ] Level-of-detail (LOD) optimization
- [ ] Mesh simplification algorithms

## **🎯 COMPLETED FEATURES ✅**
- [x] **Interactive FDF Controls** - WASD movement, QE rotation, mouse zoom
- [x] **Math3D Library** - Complete vector and matrix operations
- [x] **Multi-Projection System** - 6 different projection modes:
  - [x] Isometric (default 3D view)
  - [x] Perspective (realistic 3D with depth) 
  - [x] Orthographic (technical drawing view)
  - [x] Top-Down (perfect for PNG heightmaps)
  - [x] Front View (X-Z plane view)
  - [x] Side View (Y-Z plane view)
- [x] **Projection Cycling** - P key to switch between modes
- [x] **Format Structure** - Headers for STL, OBJ, image support

---
**Status**: Multi-projection system complete ✅ Math3D library complete ✅  
**Next**: Binary file reader implementation  
**Last Updated**: October 9, 2025

**Controls**: See CONTROLS.md for full usage guide
**Ready for**: PNG/image heightmap visualization with Top-Down view