
// example use to downsample an array BIG of floats from 1024 points to another array SMALL with 128 points:
// Resample(BIG, 1024, SMALL, 128);

template<int Radius>
static inline float Lanczos(float x)
{
    if (x == 0.0) return 1.0;
    if (x <= -Radius || x >= Radius) return 0.0;
    float pi_x = x * M_PI;
    return Radius * sin(pi_x) * sin(pi_x / Radius) / (pi_x * pi_x);
}

const int FilterRadius = 3;

static inline void Resample
 (std::vector<double> source, size_t src_len,
 std::vector<double> &result, size_t dest_len)
{
    const float blur = 1.0;
    const float factor = dest_len / (float)src_len;
    
    float scale   = fmin(factor, 1.0f) / blur;
    float support = FilterRadius / scale;
    
    std::vector<float> contribution(fmin(src_len, 5+size_t(2*support)));
    /* 5 = room for rounding up in calculations of start, stop and support */
    
    if (support <= 0.5f) { support = 0.5f + 1E-12; scale = 1.0f; }
    
    for (size_t x=0; x<dest_len; ++x)
    {
        float center = (x+0.5f) / factor;
        size_t start = (size_t)fmax(center-support+0.5f, (float)0);
        size_t stop  = (size_t)fmin(center+support+0.5f, (float)src_len);
        float density = 0.0f;
        size_t nmax = stop-start;
        float s = start - center+0.5f;
        result[x] = 0;
        for (size_t n=0; n<nmax; ++n, ++s)
        {
            contribution[n] = Lanczos<FilterRadius> (s * scale);
            density += contribution[n];
            result[x] += source[start+n]*contribution[n];
        }
        if (density != 0.0 && density != 1.0)
        {
            /* Normalize. */
            result[x] /= density;
        }
    }
}
