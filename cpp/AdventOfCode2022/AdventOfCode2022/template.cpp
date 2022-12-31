// Template, IGAD version 2
// IGAD/NHTV/UU - Jacco Bikker - 2006-2020

#include "precomp.h"

uint RGB32to8(const uint c) { return ((c >> 6) & 3) + (((c >> 13) & 7) << 2) + (((c >> 21) & 7) << 5); }
uint RGB32to16(const uint c) { return ((c >> 4) & 15) + (((c >> 12) & 15) << 4) + (((c >> 20) & 15) << 8); }
uint BGR32to8(const uint c) { return (((c >> 5) & 7) << 5) + (((c >> 13) & 7) << 2) + ((c >> 22) & 3); }
uint RGB16to32(const uint c) { return (((c >> 8) & 15) << 20) + (((c >> 4) & 15) << 12) + ((c & 15) << 4); }

DWORD CountSetBits(ULONG_PTR bitMask)
{
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1, bitSetCount = 0;
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	for (DWORD i = 0; i <= LSHIFT; ++i) bitSetCount += ((bitMask & bitTest) ? 1 : 0), bitTest /= 2;
	return bitSetCount;
}

// RNG - Marsaglia's xor32
static uint seed = 0x12345678;
uint RandomUInt()
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat() { return RandomUInt() * 2.3283064365387e-10f; }
float Rand(float range) { return RandomFloat() * range; }
// local seed
uint RandomUInt(uint& seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
float RandomFloat(uint& seed) { return RandomUInt(seed) * 2.3283064365387e-10f; }

// Perlin noise implementation - https://stackoverflow.com/questions/29711668/perlin-noise-generation
static int numX = 512, numY = 512, numOctaves = 7, primeIndex = 0;
static float persistence = 0.5f;
static int primes[10][3] = {
	{ 995615039, 600173719, 701464987 }, { 831731269, 162318869, 136250887 }, { 174329291, 946737083, 245679977 },
	{ 362489573, 795918041, 350777237 }, { 457025711, 880830799, 909678923 }, { 787070341, 177340217, 593320781 },
	{ 405493717, 291031019, 391950901 }, { 458904767, 676625681, 424452397 }, { 531736441, 939683957, 810651871 },
	{ 997169939, 842027887, 423882827 }
};
static float Noise(const int i, const int x, const int y)
{
	int n = x + y * 57;
	n = (n << 13) ^ n;
	const int a = primes[i][0], b = primes[i][1], c = primes[i][2];
	const int t = (n * (n * n * a + b) + c) & 0x7fffffff;
	return 1.0f - (float)t / 1073741824.0f;
}
static float SmoothedNoise(const int i, const int x, const int y)
{
	const float corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) + Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16;
	const float sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) + Noise(i, x, y + 1)) / 8;
	const float center = Noise(i, x, y) / 4;
	return corners + sides + center;
}
static float Interpolate(const float a, const float b, const float x)
{
	const float ft = x * 3.1415927f, f = (1 - cosf(ft)) * 0.5f;
	return a * (1 - f) + b * f;
}
static float InterpolatedNoise(const int i, const float x, const float y)
{
	const int integer_X = (int)x, integer_Y = (int)y;
	const float fractional_X = x - integer_X, fractional_Y = y - integer_Y;
	const float v1 = SmoothedNoise(i, integer_X, integer_Y);
	const float v2 = SmoothedNoise(i, integer_X + 1, integer_Y);
	const float v3 = SmoothedNoise(i, integer_X, integer_Y + 1);
	const float v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1);
	const float i1 = Interpolate(v1, v2, fractional_X);
	const float i2 = Interpolate(v3, v4, fractional_X);
	return Interpolate(i1, i2, fractional_Y);
}
float noise2D(const float x, const float y)
{
	float total = 0, frequency = (float)(2 << numOctaves), amplitude = 1;
	for (int i = 0; i < numOctaves; ++i)
	{
		frequency /= 2, amplitude *= persistence;
		total += InterpolatedNoise((primeIndex + i) % 10, x / frequency, y / frequency) * amplitude;
	}
	return total / frequency;
}

// math implementations
mat4 operator*(const mat4& a, const mat4& b)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4)
		for (uint j = 0; j < 4; ++j)
		{
			r[i + j] =
				(a.cell[i + 0] * b.cell[j + 0]) +
				(a.cell[i + 1] * b.cell[j + 4]) +
				(a.cell[i + 2] * b.cell[j + 8]) +
				(a.cell[i + 3] * b.cell[j + 12]);
		}
	return r;
}
mat4 operator*(const mat4& a, const float s)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4) r.cell[i] = a.cell[i] * s;
	return r;
}
mat4 operator*(const float s, const mat4& a)
{
	mat4 r;
	for (uint i = 0; i < 16; i++) r.cell[i] = a.cell[i] * s;
	return r;
}
mat4 operator+(const mat4& a, const mat4& b)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4) r.cell[i] = a.cell[i] + b.cell[i];
	return r;
}
bool operator==(const mat4& a, const mat4& b)
{
	for (uint i = 0; i < 16; i++)
		if (a.cell[i] != b.cell[i]) return false;
	return true;
}
bool operator!=(const mat4& a, const mat4& b) { return !(a == b); }
float4 operator*(const mat4& a, const float4& b)
{
	return make_float4(a.cell[0] * b.x + a.cell[1] * b.y + a.cell[2] * b.z + a.cell[3] * b.w,
		a.cell[4] * b.x + a.cell[5] * b.y + a.cell[6] * b.z + a.cell[7] * b.w,
		a.cell[8] * b.x + a.cell[9] * b.y + a.cell[10] * b.z + a.cell[11] * b.w,
		a.cell[12] * b.x + a.cell[13] * b.y + a.cell[14] * b.z + a.cell[15] * b.w);
}
float4 operator*(const float4& b, const mat4& a)
{
	return make_float4(a.cell[0] * b.x + a.cell[1] * b.y + a.cell[2] * b.z + a.cell[3] * b.w,
		a.cell[4] * b.x + a.cell[5] * b.y + a.cell[6] * b.z + a.cell[7] * b.w,
		a.cell[8] * b.x + a.cell[9] * b.y + a.cell[10] * b.z + a.cell[11] * b.w,
		a.cell[12] * b.x + a.cell[13] * b.y + a.cell[14] * b.z + a.cell[15] * b.w);
}
float3 TransformPosition(const float3& a, const mat4& M)
{
	return make_float3(make_float4(a, 1) * M);
}
float3 TransformVector(const float3& a, const mat4& M)
{
	return make_float3(make_float4(a, 0) * M);
}

// Helper functions
bool FileIsNewer(const char* file1, const char* file2)
{
	struct stat f1;
	struct stat f2;

	auto ret = stat(file1, &f1);

	if (stat(file2, &f2)) return true; // second file does not exist

#ifdef _MSC_VER
	return f1.st_mtime >= f2.st_mtime;
#else
	if (f1.st_mtim.tv_sec >= f2.st_mtim.tv_sec)
		return true;
	return f1.st_mtim.tv_nsec >= f2.st_mtim.tv_nsec;
#endif
}

bool FileExists(const char* f)
{
	ifstream s(f);
	return s.good();
}

bool RemoveFile(const char* f)
{
	if (!FileExists(f)) return false;
	return !remove(f);
}

uint FileSize(string filename)
{
	ifstream s(filename);
	return s.good();
}

string TextFileRead(const char* _File)
{
	ifstream s(_File);
	string str((istreambuf_iterator<char>(s)), istreambuf_iterator<char>());
	s.close();
	return str;
}

int LineCount(const string s)
{
	const char* p = s.c_str();
	int lines = 0;
	while (*p) if (*p++ == '\n') lines++;
	return lines;
}

void TextFileWrite(const string& text, const char* _File)
{
	ofstream s(_File, ios::binary);
	int len = (int)text.size();
	s.write((const char*)&len, sizeof(len));
	s.write(text.c_str(), len);
}

vector<string> StringSplit(string s, string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

bool StartsWith(string s, string pattern)
{
	return !strncmp(s.c_str(), pattern.c_str(), pattern.size());
}

bool will_overflow(long long a, long long b)
{
	return(b > LLONG_MAX / a);
}

void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
		}));
}

void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
		}).base(), s.end());
}

void trim(std::string& s) {
	rtrim(s);
	ltrim(s);
}

std::string ltrim_copy(std::string s) {
	ltrim(s);
	return s;
}

std::string rtrim_copy(std::string s) {
	rtrim(s);
	return s;
}

std::string trim_copy(std::string s) {
	trim(s);
	return s;
}
