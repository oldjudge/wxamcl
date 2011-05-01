#include "main.h"

Decompressor::Decompressor()
{
	Init();
}

Decompressor::~Decompressor()
{
	//if (m_ucdata)
	//	delete[] m_ucdata;
	inflateEnd(&m_z);
}

void Decompressor::Init()
{
	//m_ucdata = NULL;
	m_uclen = 0;
	m_cbytes = 0;
	m_ucbytes = 0;
	m_len = 0;
	m_err=0;
	m_z.zalloc = Z_NULL;
	m_z.zfree = Z_NULL;
	m_z.opaque = Z_NULL;
	//z.next_in = Z_NULL;
	m_z.avail_in = 0;
	m_z.next_in = Z_NULL;
	m_z.total_in=0;
	m_z.total_out=0;
	inflateInit(&m_z);
	m_ratio = 0.0;
}

int Decompressor::Decompress(char *data, size_t len, size_t out)
{
	m_len = len;
	
	m_z.next_in = (Bytef*)data;
	m_z.avail_in = (uInt)m_len;
	m_z.next_out = (Bytef*)m_ucdata;
	m_z.avail_out = (uInt)out;
	//err = inflateSync(z);

	m_err = inflate(&m_z, Z_SYNC_FLUSH);
	
	if (m_err==Z_STREAM_END) {
		memcpy (m_ucdata, m_z.next_in, m_z.avail_in);
		inflateEnd(&m_z);
		return -1;
		}
	if (m_err==Z_MEM_ERROR) {
		inflateEnd(&m_z);
		return -1;
		}
	if (m_err==Z_BUF_ERROR) {
		//inflateEnd(&z);
		//boMCCP2 = FALSE;
		return -1;
		}

	if (m_err==Z_DATA_ERROR) {
		m_err=inflateSync(&m_z);
		while(m_err==Z_DATA_ERROR)
			m_err=inflateSync(&m_z);
		if (!m_err) {
			inflate(&m_z, Z_SYNC_FLUSH);
			return 0;
			}
		inflateEnd(&m_z);
		return -1;
		}
	m_uclen = m_z.total_out-m_ucbytes;
	//wxASSERT_MSG((m_uclen!=0), wxString::Format(wxT("%d"), m_uclen));
	m_ucdata[m_uclen]=(char)EOS;
	m_cbytes = m_z.total_in;
	m_ucbytes = m_z.total_out;
	m_ratio = (float)m_cbytes/m_ucbytes;
	m_ratio = 1 - m_ratio;
	return 0;
}

int Decompressor::Decompress(wxString data, size_t len, size_t out)
{
	m_len = len;
	//m_cdata = new wxChar[len];
	/*if (sizeof(m_ucdata)!=0)
	{
		delete[] m_ucdata;
		m_ucdata=NULL;
	}*/
	//m_ucdata = new wxChar[out];

	//m_cdata = data;
	char s[5000];
	strncpy(s, data.To8BitData().data(), data.length());
	//s = (char*)data.char_str();
	//m_z.next_in = (Bytef*)s;//data.char_str();
	m_z.next_in = (Bytef*)(char*)data.To8BitData().data();
	m_z.avail_in = (uInt)m_len;
	m_z.next_out = (Bytef*)m_ucdata;
	m_z.avail_out = (uInt)out;
	//err = inflateSync(z);
	m_err = inflate(&m_z, Z_SYNC_FLUSH);
	if (m_err==Z_STREAM_END) {
		memcpy (m_ucdata, m_z.next_in, m_z.avail_in);
		inflateEnd(&m_z);
		return -1;
		}
	if (m_err==Z_MEM_ERROR) {
		inflateEnd(&m_z);
		return -1;
		}
	if (m_err==Z_BUF_ERROR) {
		//inflateEnd(&z);
		//boMCCP2 = FALSE;
		return -1;
		}

	if (m_err==Z_DATA_ERROR) {
		m_err=inflateSync(&m_z);
		if (!m_err) {
			inflate(&m_z, Z_SYNC_FLUSH);
			return 0;
			}
		inflateEnd(&m_z);
		return -1;
		}
	m_uclen = m_z.total_out-m_ucbytes;
	//wxASSERT_MSG((m_uclen!=0), wxString::Format(wxT("%d"), m_uclen));
	m_ucdata[m_uclen]=(char)EOS;
	m_cbytes = m_z.total_in;
	m_ucbytes = m_z.total_out;
	m_ratio = (float)m_cbytes/m_ucbytes;
	m_ratio = 1 - m_ratio;
	return 0;
}

void Decompressor::GetUCBuffer(char* data)
{
	wxStrcpy(data, m_ucdata);
}

void Decompressor::EndDecompress()
{
	//if (m_ucdata)
	//	delete[] m_ucdata;
	inflateEnd(&m_z);
}
