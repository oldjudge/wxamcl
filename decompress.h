class Decompressor
{
public:
	Decompressor();
	~Decompressor();

	int Decompress(char *data, size_t len=0, size_t out=100000);//decompress the data, return 0 or error code
	int Decompress(wxString data, size_t len=0, size_t out=100000);//decompress the data, return 0 or error code
	void GetUCBuffer(char *data);//Get the uncompressed data...provide a buffer big enough!
	size_t GetUCLen() {return m_uclen;}//how much uncompressed data is there?
	float GetRatio() {return m_ratio;}
    void EndDecompress();
	void Init();
private:
	char m_ucdata[128001];
	size_t m_len;
	struct z_stream_s m_z;
	int m_err;
	size_t m_cbytes;
	size_t m_ucbytes;
	size_t m_uclen;
	float m_ratio;
};
