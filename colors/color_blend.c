int color_blend(int start_color,int end_color, double t)
{
    if(start_color == -1)
        start_color = 0xFFFFFF;
    if(end_color == -1)
        end_color = 0xFFFFFF;

    // clamp t between 0.0 and 1.0
    // t = inrerpolation factor (karışım oranı)
    if(t < 0.0)
        t = 0.0;
    if(t > 1.0)
        t = 1.0;
    
    // extract rgb components from start color
    int r1 = (start_color >> 16) & 0xFF;
    int g1 = (start_color >> 8) & 0xFF;
    int b1 = start_color & 0xFF; 
    
    // extract rgb components from end color
    int r2 = (end_color >> 16) & 0xFF;
    int g2 = (end_color >> 8) & 0xFF;
    int b2 = end_color & 0xFF;

    // linear interpolation for each component
    int r = (int)(r1 + (r2 - r1) * t);
    int g = (int)(g1 + (g2 - g1) * t);
    int b = (int)(b1 + (b2 - b1) * t);
    // combine RGB back to int
    return((r << 16) | (g << 8) | b);
}