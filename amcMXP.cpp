#include "main.h"

int amcMXP::m_parsestate = MXP_TEXT;

amcMXP::amcMXP(MudWindow *mw)
{
	SetColors();
	m_tagopen = false;
	m_mxpmode = MXP_MODE_OPEN;
	m_parent = mw;
}

amcMXP::~amcMXP()
{
	m_elems.clear();
}

void amcMXP::SetColors()
{
wxColour c;
	c.Set(240, 248, 255);
	m_mxpcolor["aliceblue"] = c;
	c.Set(250, 235, 215);
	m_mxpcolor["antiquewhite"] = c;
	c.Set(0, 255, 255);
	m_mxpcolor["aqua"] = c;
	c.Set(127, 255, 212);
	m_mxpcolor["aquamarine"] = c;
	c.Set(240, 255, 255);
	m_mxpcolor["azure"] = c;
	c.Set(245, 245, 220);
	m_mxpcolor["beige"] = c;
	c.Set(255, 228, 220);
	m_mxpcolor["bisque"] = c;
	c.Set(0, 0, 0);
	m_mxpcolor["black"] = c;
	c.Set(255, 235, 205);
	m_mxpcolor["blanchedalmond"] = c;
	c.Set(0, 0, 255);
	m_mxpcolor["blue"] = c;
	c.Set(138, 43, 226);
	m_mxpcolor["blueviolet"] = c;
	c.Set(165, 42, 42);
	m_mxpcolor["brown"] = c;
	c.Set(222, 184, 135);
	m_mxpcolor["burlywood"] = c;
	c.Set(95, 158, 160);
	m_mxpcolor["cadetblue"] = c;
	c.Set(127, 255, 0);
	m_mxpcolor["chartreuse"] = c;
	c.Set(210, 105, 30);
	m_mxpcolor["chocolate"] = c;
	c.Set(255, 127, 80);
	m_mxpcolor["coral"] = c;
	c.Set(100, 149, 237);
	m_mxpcolor["cornflowerblue"] = c;
	c.Set(255, 248, 220);
	m_mxpcolor["cornsilk"] = c;
	c.Set(220, 20, 60);
	m_mxpcolor["crimson"] = c;
	c.Set(0, 255, 255);
	m_mxpcolor["cyan"] = c;
	c.Set(0, 0, 139);
	m_mxpcolor["darkblue"] = c;
	c.Set(0, 139, 139);
	m_mxpcolor["darkcyan"] = c;
	c.Set(184, 134, 11);
	m_mxpcolor["darkgoldenrod"] = c;
	c.Set(169, 169, 169);
	m_mxpcolor["darkgray"] = c;
	c.Set(0, 100, 0);
	m_mxpcolor["darkgreen"] = c;
	c.Set(189, 183, 107);
	m_mxpcolor["darkkhaki"] = c;
	c.Set(139, 0, 139);
	m_mxpcolor["darkmagenta"] = c;
	c.Set(85, 107, 47);
	m_mxpcolor["darkolivegreen"] = c;
	c.Set(255, 140, 0);
	m_mxpcolor["darkorange"] = c;
	c.Set(153, 50, 204);
	m_mxpcolor["darkorchid"] = c;
	c.Set(139, 0, 0);
	m_mxpcolor["darkred"] = c;
	c.Set(233, 150, 122);
	m_mxpcolor["darksalmon"] = c;
	c.Set(141, 188, 143);
	m_mxpcolor["darkseagreen"] = c;
	c.Set(72, 61, 139);
	m_mxpcolor["darkslateblue"] = c;
	c.Set(47, 79, 79);
	m_mxpcolor["darkslategray"] = c;
	c.Set(0, 222, 209);
	m_mxpcolor["darkturquoise"] = c;
	c.Set(148, 0, 211);
	m_mxpcolor["darkviolet"] = c;
	c.Set(255, 20, 147);
	m_mxpcolor["deeppink"] = c;
	c.Set(0, 191, 255);
	m_mxpcolor["deepskyblue"] = c;
	c.Set(105, 105, 105);
	m_mxpcolor["dimgray"] = c;
	c.Set(30, 144, 255);
	m_mxpcolor["dodgerblue"] = c;
	c.Set(178, 34, 34);
	m_mxpcolor["firebrick"] = c;
	c.Set(255, 250, 240);
	m_mxpcolor["floralwhite"] = c;
	c.Set(34, 139, 34);
	m_mxpcolor["forestgreen"] = c;
	c.Set(255, 0, 255);
	m_mxpcolor["fuchsia"] = c;
	c.Set(220, 220, 220);
	m_mxpcolor["gainsboro"] = c;
	c.Set(248, 248, 255);
	m_mxpcolor["ghostwhite"] = c;
	c.Set(255, 215, 0);
	m_mxpcolor["gold"] = c;
	c.Set(218, 165, 32);
	m_mxpcolor["goldenrod"] = c;
	c.Set(128, 128, 128);
	m_mxpcolor["gray"] = c;
	c.Set(0, 128, 0);
	m_mxpcolor["green"] = c;
	c.Set(173, 255, 47);
	m_mxpcolor["greenyellow"] = c;
	c.Set(240, 255, 240);
	m_mxpcolor["honeydew"] = c;
	c.Set(255, 105, 180);
	m_mxpcolor["hotpink"] = c;
	c.Set(205, 92, 92);
	m_mxpcolor["indianred"] = c;
	c.Set(75, 0, 130);
	m_mxpcolor["indigo"] = c;
	c.Set(255, 255, 240);
	m_mxpcolor["ivory"] = c;
	c.Set(240, 230, 140);
	m_mxpcolor["khaki"] = c;
	c.Set(230, 230, 250);
	m_mxpcolor["lavender"] = c;
	c.Set(255, 240, 245);
	m_mxpcolor["lavenderblush"] = c;
	c.Set(124, 252, 0);
	m_mxpcolor["lawngreen"] = c;
	c.Set(255, 250, 205);
	m_mxpcolor["lemonchiffon"] = c;
	c.Set(173, 216, 230);
	m_mxpcolor["lightblue"] = c;
	c.Set(240, 128, 128);
	m_mxpcolor["lightcoral"] = c;
	c.Set(224, 255, 255);
	m_mxpcolor["lightcyan"] = c;
	c.Set(250, 250, 210);
	m_mxpcolor["lightgoldenrodyellow"] = c;
	c.Set(211, 211, 211);
	m_mxpcolor["lightgray"] = c;
	c.Set(144, 238, 144);
	m_mxpcolor["lightgreen"] = c;
	c.Set(211, 211, 211);
	m_mxpcolor["lightgrey"] = c;
	c.Set(255, 182, 193);
	m_mxpcolor["lightpink"] = c;
	c.Set(255, 160, 122);
	m_mxpcolor["lightsalmon"] = c;
	c.Set(32, 178, 170);
	m_mxpcolor["lightseagreen"] = c;
	c.Set(135, 206, 250);
	m_mxpcolor["lightskyblue"] = c;
	c.Set(119, 136, 153);
	m_mxpcolor["lightslategray"] = c;
	c.Set(176, 196, 222);
	m_mxpcolor["lightsteelblue"] = c;
	c.Set(255, 255, 224);
	m_mxpcolor["lightyellow"] = c;
	c.Set(0, 255, 0);
	m_mxpcolor["lime"] = c;
	c.Set(50, 205, 50);
	m_mxpcolor["limegreen"] = c;
	c.Set(250, 240, 230);
	m_mxpcolor["linen"] = c;
	c.Set(255, 0, 255);
	m_mxpcolor["magenta"] = c;
	c.Set(128, 0, 0);
	m_mxpcolor["maroon"] = c;
	c.Set(102, 205, 170);
	m_mxpcolor["mediumaquamarine"] = c;
	c.Set(0, 0, 170);
	m_mxpcolor["mediumblue"] = c;
	c.Set(186, 85, 211);
	m_mxpcolor["mediumorchid"] = c;
	c.Set(147, 112, 219);
	m_mxpcolor["mediumpurple"] = c;
	c.Set(60, 179, 113);
	m_mxpcolor["mediumseagreen"] = c;
	c.Set(123, 104, 238);
	m_mxpcolor["mediumslateblue"] = c;
	c.Set(0, 250, 154);
	m_mxpcolor["mediumspringgreen"] = c;
	c.Set(72, 209, 204);
	m_mxpcolor["mediumturquoise"] = c;
	c.Set(199, 21, 133);
	m_mxpcolor["mediumvioletred"] = c;
	c.Set(25, 25, 112);
	m_mxpcolor["midnightblue"] = c;
	c.Set(245, 255, 250);
	m_mxpcolor["mintcream"] = c;
	c.Set(255, 228, 225);
	m_mxpcolor["mistyrose"] = c;
	c.Set(255, 228, 181);
	m_mxpcolor["mocassin"] = c;
	c.Set(255, 222, 173);
	m_mxpcolor["navajowhite"] = c;
	c.Set(0, 0, 128);
	m_mxpcolor["navy"] = c;
	c.Set(253, 245, 230);
	m_mxpcolor["oldlace"] = c;
	c.Set(128, 128, 0);
	m_mxpcolor["olive"] = c;
	c.Set(107, 142, 35);
	m_mxpcolor["olivedrab"] = c;
	c.Set(255, 165, 0);
	m_mxpcolor["orange"] = c;
	c.Set(255, 69, 0);
	m_mxpcolor["orangered"] = c;
	c.Set(218, 112, 214);
	m_mxpcolor["orchid"] = c;
	c.Set(238, 232, 170);
	m_mxpcolor["palegoldenrod"] = c;
	c.Set(152, 251, 152);
	m_mxpcolor["palegreen"] = c;

	c.Set(175, 238, 238);
	m_mxpcolor["paleturquoise"] = c;
	c.Set(219, 112, 147);
	m_mxpcolor["palevioletred"] = c;
	c.Set(255, 239, 213);
	m_mxpcolor["papayawhip"] = c;
	c.Set(255, 218, 185);
	m_mxpcolor["peachpuff"] = c;
	c.Set(205, 133, 63);
	m_mxpcolor["peru"] = c;
	c.Set(255, 200, 203);
	m_mxpcolor["pink"] = c;
	c.Set(221, 160, 221);
	m_mxpcolor["plum"] = c;
	c.Set(176, 224, 230);
	m_mxpcolor["powderblue"] = c;
	c.Set(128, 0, 128);
	m_mxpcolor["purple"] = c;
	c.Set(255, 0, 0);
	m_mxpcolor["red"] = c;
	c.Set(188, 143, 143);
	m_mxpcolor["rosybrown"] = c;
	c.Set(65, 105, 225);
	m_mxpcolor["royalblue"] = c;
	c.Set(139, 69, 19);
	m_mxpcolor["saddlebrown"] = c;
	c.Set(250, 128, 114);
	m_mxpcolor["salmon"] = c;
	c.Set(244, 164, 96);
	m_mxpcolor["sandybrown"] = c;
	c.Set(46,139,87);
	m_mxpcolor["seagreen"] = c;
	c.Set(255, 245, 238);
	m_mxpcolor["seashell"] = c;
	c.Set(160, 82, 45);
	m_mxpcolor["sienna"] = c;
	c.Set(192, 192, 192);
	m_mxpcolor["silver"] = c;
	c.Set(135, 206, 235);
	m_mxpcolor["skyblue"] = c;
	c.Set(106, 90, 205);
	m_mxpcolor["slateblue"] = c;
	c.Set(112, 128, 144);
	m_mxpcolor["slategray"] = c;
	c.Set(255, 250, 250);
	m_mxpcolor["snow"] = c;
	c.Set(0, 255, 127);
	m_mxpcolor["springgreen"] = c;
	c.Set(70, 130, 180);
	m_mxpcolor["steelblue"] = c;

	c.Set(210, 180, 140);
	m_mxpcolor["tan"] = c;
	c.Set(0, 128, 128);
	m_mxpcolor["teal"] = c;
	c.Set(216, 191, 216);
	m_mxpcolor["thistle"] = c;
	c.Set(255, 99, 71);
	m_mxpcolor["tomato"] = c;
	c.Set(64, 224, 208);
	m_mxpcolor["turquoise"] = c;
	c.Set(238, 130, 238);
	m_mxpcolor["violet"] = c;
	c.Set(245, 222, 179);
	m_mxpcolor["wheat"] = c;
	c.Set(255, 255, 255);
	m_mxpcolor["white"] = c;
	c.Set(245, 245, 245);
	m_mxpcolor["whitesmoke"] = c;
	c.Set(255, 255, 0);
	m_mxpcolor["yellow"] = c;
	c.Set(154, 205, 50);
	m_mxpcolor["yellowgreen"] = c;
}

bool amcMXP::Parse(wxString s)
{
wxString::iterator it;
amcMXPTag aTag;
static amcMXPTag oldTag;
amcMXPTag escTag;
amcMXPTag iacTag;
static wxString olds = wxEmptyString;
static amcMXPTag oldescTag;
static wxString oldsimple = wxEmptyString;
size_t pos=0;
static size_t oldpos=0;
AnsiLine line;
AnsiLineElement ale;
wxString simpleText = wxEmptyString;
int elemnum=0;
MudWindow *mw = m_parent;//wxGetApp().GetChild();
static bool parsing = true;
static bool element = false;
static bool intagtext = false;
	//m_parsestate = MXP_TEXT;
	
	s.Replace("<br>", "\n");
	s.Replace("<BR>", "\n");
	s.Replace("\r\n", "\n");
	s.Replace("\n\r", "\n");
	s.Replace("<nobr>", "");
	s.Replace("<sbr>", " ");
	//ReplaceEntities(&s);
	size_t alpha, omega;
	alpha = s.Lower().Find("<p>");
	if (alpha!=wxNOT_FOUND)
	{
		omega = s.Lower().Find("</p>");
		if (omega==wxNOT_FOUND)
			omega=s.length();
		for (int i=alpha;i<omega;i++)
		{
			if (s.GetChar(i)=='\n')
				s.SetChar(i, ' ');
		}
		s.Replace("<P>", "");
		s.Replace("</P>", "");
		s.Replace("<p>", "");
		s.Replace("</p>", "");
	}
	
	if (parsing)// && oldpos)
	{
		aTag = oldTag;
		oldTag.Reset();
		escTag = oldescTag;
		oldescTag.Reset();
		s = olds+s;
		olds=wxEmptyString;
		pos = oldpos;
		oldpos = 0;
		simpleText = oldsimple + simpleText;
		//it+=pos;
	}
	it = s.begin()+pos;
	for(;it!=s.end();it++, pos++)
	{
		parsing = true;
		switch(m_parsestate)
		{
		case MXP_TEXT:
			if (*it=='<')
			{
				m_parsestate = MXP_TAG_OPEN;
			}
			else if (*it==0x1b)
			{
				m_parsestate = MXP_ESC;
				escTag.AppendText(*it);
			}
			else if (*it=='\n' && (m_mxpmode == MXP_MODE_OPEN || m_mxpmode == MXP_MODE_TEMPSECURE))
			{
				mw->ParseNBuffer((char*)"\x1b[0m", false);
				simpleText.Append(*it);
			}
			else 
				simpleText.Append(*it);
			break;
		
		case MXP_ELEMENT:
			{
			
			if (*it=='-')
			{
				m_parsestate = MXP_COMMENT;
				break;
			}
			if (pos>=2)
				pos-=2;
			//int opos = pos;
			bool b = ParseElementRex(s, &pos);
			it = s.begin()+pos;
			if (b)
			{
				m_parsestate=MXP_TAG_OPEN;
				if (pos)
				{
					
					if (pos<s.length())
					{
						pos++;
						it++;
						aTag.AppendTag(*it);//pos = opos-1;
					}
					else
					{
						it--;
						pos--;
					}
				}
				break;
			}
			if (*it=='\x1b')
			{
				m_parsestate=MXP_ESC;
				escTag.AppendText(*it);
				break;
			}
			parsing = false;
			aTag.Reset();
			m_parsestate = MXP_TEXT;
			break;
			}
		case MXP_TAG_OPEN:
			if (!simpleText.empty())
			{
				//simpleText.Trim(false);
				ReplaceEntities(&simpleText);
				mw->ParseNBuffer((char*)simpleText.To8BitData().data(), false);
				mw->GetLineStyle(mw->m_curline-1)->back().SetFontStyle(0);
				simpleText = wxEmptyString;
			}
			
			if (*it=='!')
			{
				m_parsestate = MXP_ELEMENT;
				break;
			}
			
			if (*it=='/')
			{
				m_parsestate = MXP_ENDTAG;
				m_tagopen = false;
			}
			if (*it=='>')
			{
				m_parsestate = MXP_TEXTINTAG;
				m_tagopen = true;
				elemnum = FindElement(aTag.GetTag());
				if (aTag.IsMXPTag())
				{
					if (!ParseSingleTag(&aTag))
					{
						//aTag.Reset();
						m_parsestate = MXP_TEXT;
						break;
					}
					if (elemnum==-1)
					{
						//m_parsestate = MXP_TEXT;
					}
				}
				else if (m_mxpmode==MXP_MODE_LOCKLOCKED || m_mxpmode==MXP_MODE_LOCKED)
				{
					ParseTag(&aTag, -1);
					m_parsestate = MXP_TEXT;
				}
				
			}
			
			else
				aTag.AppendTag(*it);
			break;
		case MXP_TEXTINTAG:
			if (*it=='<')
			{
				m_parsestate = MXP_ENDTAG;
				aTag.SetText(aTag.GetText().Append(escTag.GetText()));
				escTag.Reset();
				elemnum = FindElement(aTag.GetTag());
				if (aTag.IsMXPTag())
				{
					ParseSingleTag(&aTag);
					//aTag.Reset();
					break;
				}
				if (aTag.IsOpenTag())
				{
					ParseOpenTag(&aTag);
					aTag.Reset();
					break;
				}
				if (elemnum==-1)
				{
					mw->ParseNBuffer((char*)aTag.GetText().To8BitData().data(), false);
					aTag.Reset();
					break;
				}
				else
				{
					//ReplaceEntities(&simpleText);
					
					ParseTag(&aTag, elemnum);
					aTag.Reset();
				}
			}
			else if (*it==ESC)
			{
				m_parsestate = MXP_ESCINTEXTTAG;
				escTag.AppendText(*it);
				break;
			}
			else
				aTag.AppendText(*it);
			break;
		case MXP_ENDTAG:
			//mw->Refresh();
			if (*it=='/')
				m_tagopen = false;
			if (*it=='!')
			{
				m_tagopen = false;
				m_parsestate = MXP_ELEMENT;
			}
			if (*it=='>')
			{
				if (!m_tagopen)
				{
					m_parsestate = MXP_TEXT;
					if (!aTag.GetTag().Cmp("/") || aTag.GetEndTag().StartsWith("/"))
						if (!ParseSingleTag(&aTag))
						{
							//aTag.Reset();
							break;
						}
				}
				else
				{
					m_parsestate = MXP_TEXTINTAG;
					aTag.SetTag(aTag.GetEndTag());
					aTag.SetEndTag(wxEmptyString);
					break;
				}
				
				elemnum = FindElement(aTag.GetTag());
				if (elemnum==-1)
				{
					if (aTag.IsMXPTag())
					{
						if (!ParseSingleTag(&aTag))
						{
							//aTag.Reset();
							m_parsestate = MXP_TEXT;
							break;
						}
						else if (aTag.GetTag().Lower().StartsWith("send"))
							m_parsestate = MXP_TEXT;
					}
					mw->ParseNBuffer((char*)aTag.GetText().To8BitData().data(), false);
					aTag.Reset();
					break;
				}
				else
				{
					ParseTag(&aTag, elemnum);
					aTag.Reset();
				}
			}
			else 
				aTag.AppendEndTag(*it);
			//aTag.endtag += *it;
			break;
		case MXP_COMMENT:
			if (*it=='>' && *(it-1)=='-' && *(it-2)=='-')
				m_parsestate = MXP_TEXT;
			break;
		case MXP_MISC:
			if (*it=='>')
			{
				m_parsestate = MXP_TEXT;
			}
			break;
		case MXP_ESC:
			escTag.AppendText(*it);
			//aTag.AppendText(*it);
			if (*it=='m')
			{
				//mw->ParseBuffer((char*)escTag.GetText().To8BitData().data());
				//aTag.GetText().Append(escTag.GetText());
				simpleText.append(escTag.GetText());
				m_parsestate = MXP_TEXT;
				int num = FindElement(aTag.GetTag());
				if (num!=-1 && !intagtext)
				{
					if (!ParseTag(&aTag, num))
						aTag.Reset();
				}
				
				escTag.Reset();
				aTag.Reset();
			}
			if (*it=='H' || *it=='J')
			{
				aTag.AppendText(escTag.GetText());
				m_parsestate = MXP_TEXT;
				escTag.Reset();
			}
			if (*it=='z')
			{
				
				m_parsestate = MXP_TEXT;
				//m_parsestate = oldstate;
				m_mxpmode = atoi(s.substr(pos-1).c_str());
				//m_mxpmode = atoi(escTag.GetText());
				wxString msg;
				msg << "MXPMode = " << m_mxpmode;
				//mw->ParseBufferMXP(msg.char_str());
				//mw->Msg(msg);
				aTag.ReplaceEntitys();
				
				if (!aTag.IsEmpty())
				{
					elemnum = FindElement(aTag.GetTag());
					if (aTag.IsMXPTag())
					{
						ParseSingleTag(&aTag);
						//aTag.Reset();
								
					}
					if (elemnum==-1)
					{
						mw->ParseNBuffer((char*)aTag.GetText().To8BitData().data(), false);
						aTag.Reset();
						break;
					}
					else
					{
						ParseTag(&aTag, elemnum);
						aTag.Reset();
					}
				aTag.Reset();
				}
				//mw->ParseBuffer(aTag.GetText().char_str());
				if (m_mxpmode == MXP_MODE_RESET)
				{
					
					//ParseTag(&aTag);//close all open stuff etc
					mw->ParseNBuffer((char*)"\x1b[0;0m", false);
					parsing = false;
				}
				if (m_mxpmode == MXP_MODE_TEMPSECURE && *it=='\n')
				{
					//mw->ParseNBuffer("\x1b[0;0m", false);
					//mw->SetCurAnsiColour(mw->GetAnsiColor(7));
					//ParseTag(&aTag, -1);
				}
				escTag.Reset();
			}
		
			break;
		case MXP_ESCINTEXTTAG:
			escTag.AppendText(*it);
			if (*it=='m')
			{
				/*if (aTag.IsMXPTag())
				{
					if (!ParseSingleTag(&aTag))
						aTag.Reset();
					//break; ???
				}*/
				m_parsestate = MXP_TEXTINTAG;
				wxString s = escTag.GetText();
				aTag.SetText(aTag.GetText().append(s));
				escTag.Reset();
			}
			if (*it=='z')
			{
				escTag.Reset();
				m_parsestate = MXP_TEXTINTAG;
			}
		
			break;
		}	
		
	}
	
	if (!simpleText.empty())
	{
		ReplaceEntities(&simpleText);
		mw->ParseNBuffer((char*)simpleText.To8BitData().data(), false);
		
			//mw->m_curline++;
		if (escTag.GetText().empty())
			parsing = false;
	}
	
	if (parsing)
	{
		oldTag = aTag;
		oldescTag = escTag;
		olds = s;
		oldpos = pos;
		//oldsimple = simpleText;
	}
	
return false;
}

bool amcMXP::ParseSingleTag(amcMXPTag *t)
{
//Parse all Tags IsMXPTag returns true
//RegExp comm("send href=('|\")?([\\?|\\w|&|;|\\s|\\||#|\\d|\\-|\\.|\\/|\\(|\\)]+)('|\")?(?: PROMPT|prompt)?");
RegExp comm("send (?:prompt |hint=.+ )?(?:prompt |hint=.+ )?(?:href=)?('|\")?([\\?|\\w|&|;|\\s|\\||#|\\d|\\-|\\.|\\/|\\(|\\)]+)('|\")?(?: PROMPT|prompt)?");
//RegExp r("send (?:hint=.+ |prompt )?(?:hint=.+ |prompt )?(?:href=)?('|\")([\\?+|\\w+|&+|;+|\\s+|\\+||#+|\\d+|\\-+|\\.+|\\!+|\\(+|\\)+]+)('|\")?(?: PROMPT|prompt)?");
RegExp hint("(?:HINT|hint)=(?:\"|')([\\w|&|;|\\s|\\||\\d|\\-|\\!|\\.]+)(?:\"|')");
RegExp color("(?:c(?:olor)? |C(?:OLOR)? )(?:fore=|FORE=)?((?!back=)[\\w|\\d|#]+)?\\s?(?:back=|BACK=)?([\\w|\\d|#]+)?");
RegExp a("a href=('|\")([\\w|&|;|\\s|\\||#|\\d|\\-|\\.|\\/|\\(|\\)]+)('|\")");
MudMainFrame *f = wxGetApp().GetFrame();
MudWindow *mw = m_parent;	
	t->ReplaceEntitys();
	if (m_mxpmode==MXP_MODE_LOCKLOCKED || m_mxpmode==MXP_MODE_LOCKED)
	{
		wxString s ="<"+t->GetTag()+">";
		mw->ParseNBuffer((char*)s.To8BitData().data(), false);
		t->Reset();
		return false;
	}
	wxString ss = t->GetTag().BeforeFirst(' ').Lower();
	vector<wxString> v_parms;
	v_parms = SplitString(" ", t->GetTag().AfterFirst(' '));
	if (t->GetTag().Lower().StartsWith("send"))
	{
		if (t->GetText().empty())
			return true;
		amcMXPElement el;
		el.AppendAction(t->GetTag().Lower());
		el.BuildMXPSendCommands();
		el.BuildAttributes();
		if (el.GetAction().Lower().Find("prompt")!=wxNOT_FOUND)
			el.SetPromptFlag(true);
		int oldline = mw->m_curline-1;
		if (oldline<0)
			oldline = 0;
		int oi = 0;
		//if (!mw->GetLines()->empty())
			//mw->GetLineStyle(oldline)->size()-1;
		wxString send = t->GetText();
		mw->ParseNBuffer((char*)send.To8BitData().data(), false);
		//f->m_child->ParseBuffer(send.char_str());
		int on = 0;
		//if (!mw->GetLines()->empty())
			//mw->GetLineStyle(oldline)->size()-1;
		int newline = mw->m_curline-1;
		if (newline<0)
			newline = 0;
		int start, end;
		mw->GetLineIndices(&start, &end);
		if (start>end)
			start = end;
		//start++;
		if (start==1 && end==1)
		{
			start=0;
		}
		oldline = newline;
		ale_it it;// = f->m_child->GetLineStyle(oldline)->begin();
		//it+=oi;
		//x=0;
		///***for (it = f->m_child->GetLineStyle(oldline)->begin()+oi+1;it!=f->m_child->GetLineStyle(oldline)->end();it++)
		for (it = mw->GetLineStyle(oldline)->begin()+start;it!=mw->GetLineStyle(oldline)->begin()+end;it++)
		{
			if (el.HasPromptFlag())
				it->SetPromptSend(true);
			it->SetMXPSend(true);
			it->SetFontStyle(4);
			wxString line = el.GetAction();//t->GetTag().Lower();
			if (comm.Match(line))
			{
				vector<wxString>::iterator sit;
				for (sit = el.GetSendCommands()->begin();sit!=el.GetSendCommands()->end();sit++)
				{
					wxString command = *sit;
					command.Replace("&text;", t->GetStrippedText());//t->GetText());
					ReplaceEntities(&command);
					if (!v_parms.empty() && el.HasAttributes())
					{
						vector<wxString>::iterator vit;
						int i=0;
						for (vit=v_parms.begin();vit!=v_parms.end();vit++, i++)
						{
							command.Replace("&"+el.GetAttributes()->at(i)+";", *vit);
							
						}
					}
					command.Replace("&quot;", "\"");
					it->AddMXPCommand(command);
				}
				for (sit = el.GetLabels()->begin();sit!=el.GetLabels()->end();sit++)
				{
					wxString command = *sit;
					command.Replace("&text;", t->GetStrippedText());//t->GetText());
					ReplaceEntities(&command);
					if (!v_parms.empty() && el.HasAttributes())
					{
						vector<wxString>::iterator vit;
						int i=0;
						for (vit=v_parms.begin();vit!=v_parms.end();vit++, i++)
						{
							command.Replace("&"+el.GetAttributes()->at(i)+";", *vit);
							//hint.Replace("&"+el.GetAttributes()->at(i)+";", *vit);
						}
					}
					//command.Replace("&quot;", "\"");
					it->AddMXPLabel(command);
				}
				//hint.Replace("|", "\n");
				it->SetHint(el.GetHint());				
				/*it->AddMXPCommand(comm.GetMatch(1));
				it->AddMXPLabel(comm.GetMatch(1));
				it->SetHint(comm.GetMatch(1));*/
			}
			else
			{
				it->AddMXPCommand(t->GetStrippedText());
				it->AddMXPLabel(t->GetStrippedText());
				if (el.GetHint().empty())
					it->SetHint(t->GetStrippedText());
				else it->SetHint(el.GetHint());
			}
			ale_it tt = it;
			/*if (tt>= mw->GetLineStyle(oldline)->begin()+1)
			{
				tt--;
				it->SetFCol(tt->GetFColIndex(), tt->GetFCol());
				it->SetBCol(tt->GetBColIndex(), tt->GetBCol());
			}*/
		}
		
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("color") || t->GetTag().Lower().StartsWith("c"))
	{
		AnsiLineElement ale;
		wxColour c, b;
		b.Set("BLACK");
		c.Set("GREY");
		if (color.Match(t->GetTag()))
		{
			if (color.GetMatch(0).length())
			{
				if (color.GetMatch(0).StartsWith("#"))
					c.Set(color.GetMatch(0));
				else
					c = m_mxpcolor[color.GetMatch(0)];
			}
			if (color.GetMatch(1).length())
			{
				if (color.GetMatch(1).StartsWith("#"))
					b.Set(color.GetMatch(1));
				else
					b = m_mxpcolor[color.GetMatch(1)];
			}
			

		}
		
		ale.SetText(t->GetText());
		ale.SetFCol(99, c);
		ale.SetBCol(99, b);
		if (!mw->GetLines()->back().IsFull())
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		else
		{
			AnsiLine l;
			l.SetDateTime(wxDateTime::UNow());
			mw->GetLines()->push_back(l);
			mw->m_curline++;
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		}
		mw->GetLines()->back().SetFull(false);
		t->Reset();
	}
	else if (t->GetEndTag().Lower().StartsWith("color"))
	{
		AnsiLineElement ale;
		wxColour c;
		
		//c = f->m_child->GetAnsiColor(7);
		c = mw->GetCurAnsiColour();
		ale.SetText(wxEmptyString);
		ale.SetFCol(7, c);
		ale.SetBCol(0, c.Set("BLACK"));
		mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("a ") || t->GetTag().Lower().IsSameAs('a'))
	{
		if (t->GetText().empty())
			return true;
		
		AnsiLineElement ale;
		ale.SetText(t->GetText());
		ale.SetFontStyle(4);
		ale.SetURL(true);
		if (a.Match(t->GetTag().Lower()))
			ale.SetURLText(a.GetMatch(1));
		if (hint.Match(t->GetTag().Lower()))
			ale.SetHint(hint.GetMatch(0));
		if (!mw->GetLines()->back().IsFull())
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		else
		{
			AnsiLine l;
			l.SetDateTime(wxDateTime::UNow());
			mw->GetLines()->push_back(l);
			mw->m_curline++;
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		}
		mw->GetLines()->back().SetFull(false);
		t->Reset();
	}
	else if (!ss.Cmp("user"))
	{
		if (f->GetCurHost()!=-1)
			f->m_child->Write(f->GetHosts()->at(f->GetCurHost()).GetCharName()+'\n');
		//else f->m_child->Write("Asarean\n");
		t->Reset();
	}
	else if (!ss.Cmp("password"))
	{
		if (f->GetCurHost()!=-1)
			f->m_child->Write(f->GetHosts()->at(f->GetCurHost()).GetPwd()+'\n');
		t->Reset();
	}
	else if (!ss.Cmp("version"))
	{
		wxString sss = "\x1b[1z<VERSION MXP=\"1.0\" CLIENT=\"wxAmc\" VERSION=\"0.1\">\n";
		f->m_child->Write(sss.To8BitData());
		t->Reset();
	}
	else if (!ss.Cmp("support"))
	{
		wxString sss = "\x1b[1z<SUPPORTS -image +send +user +password +version +color +b +bold +i +italic +u +underlined -s +br +sbr>\n";
		f->m_child->Write(sss.To8BitData());
		t->Reset();
	}
	else if (!ss.Cmp("expire"))
	{
		//f->m_child->ParseBuffer(t->GetText().char_str());
		t->Reset();
	}
	else
	{
		//t->GetText().Replace("<BR>", "\r\n");
		if (t->GetEndTag().empty() && !t->GetTag().empty() && !t->GetText().empty())
		{
			t->Reset();
			return true;
		}
		if (!t->GetText().empty())
			mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
		//return true;
		t->Reset();
	}
return false;
}

bool amcMXP::ParseOpenTag(amcMXPTag *t)
{
wxString send;
	MudMainFrame *f = wxGetApp().GetFrame();
	MudWindow *mw = m_parent;
	t->ReplaceEntitys();
	if (m_mxpmode==MXP_MODE_LOCKLOCKED || m_mxpmode==MXP_MODE_LOCKED)
	{
		wxString s ="<"+t->GetTag()+">";
		mw->ParseNBuffer((char*)s.To8BitData().data(), false);
		t->Reset();
		return false;
	}
	wxString ss = t->GetTag().BeforeFirst(' ').Lower();
	vector<wxString> v_parms;
	v_parms = SplitString(" ", t->GetTag().AfterFirst(' '));
	if (t->GetEndTag().Lower().StartsWith("bold") || ! t->GetEndTag().Lower().CmpNoCase("b"))
	{
		mw->ParseNBuffer("\x1b[22m", false);
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("bold") || ! t->GetTag().Lower().CmpNoCase("b"))
	{
		send = "\x1b[1m"+t->GetText();
		mw->ParseNBuffer((char*)send.To8BitData().data(), false);
		t->Reset();
	}
	else if (t->GetEndTag().Lower().StartsWith("italic") || ! t->GetEndTag().Lower().CmpNoCase("i"))
	{
		mw->ParseNBuffer("\x1b[23m", false);
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("italic") || ! t->GetTag().Lower().CmpNoCase("i"))
	{
		//f->m_child->ParseNBuffer("\x1b[3m", false);
		AnsiLineElement ale;
		ale.SetFontStyle(3);
		ale.SetText(t->GetStrippedText());
		if (!mw->GetLines()->back().IsFull())
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		else
		{
			AnsiLine l;
			mw->GetLines()->push_back(l);
			mw->m_curline++;
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		}
		mw->GetLines()->back().SetFull(false);
		mw->GetLines()->back().SetLineText(t->GetStrippedText());
		t->Reset();
	}
	else if (t->GetEndTag().Lower().StartsWith("underline") || ! t->GetEndTag().Lower().CmpNoCase("u"))
	{
		mw->ParseNBuffer("\x1b[24m", false);
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("underline") || ! t->GetTag().Lower().CmpNoCase("u"))
	{
		//f->m_child->ParseNBuffer("\x1b[3m", false);
		AnsiLineElement ale;
		ale.SetFontStyle(4);
		ale.SetText(t->GetStrippedText());
		if (!mw->GetLines()->back().IsFull())
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		else
		{
			AnsiLine l;
			mw->GetLines()->push_back(l);
			mw->m_curline++;
			mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
		}
		mw->GetLines()->back().SetFull(false);
		t->Reset();
	}
	else if (t->GetTag().Lower().StartsWith("strikeout") || ! t->GetTag().Lower().CmpNoCase("s"))
	{
		send = "\x1b[1m"+t->GetText();
		mw->ParseNBuffer(send.char_str(), false);
		t->Reset();
	}
	else if (t->GetEndTag().Lower().StartsWith("strikeout") || ! t->GetEndTag().Lower().CmpNoCase("s"))
	{
		mw->ParseNBuffer("\x1b[22m", false);
		t->Reset();
	}
	else
	{
		//t->GetText().Replace("<BR>", "\r\n");
		if (t->GetEndTag().empty() && !t->GetTag().empty() && !t->GetText().empty())
		{
			t->Reset();
			return true;
		}
		if (!t->GetText().empty())
			mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
		//f->m_child->ParseBuffer(t->GetText().char_str());
		t->Reset();
	}
return false;
}

bool amcMXP::ParseTag(amcMXPTag *t, int elnum)
{
//RegExp comm("send href=(\"|')(.*)(\"|')");
RegExp comm("send href=('|\")([\\w|&|;|\\s|\\||#|\\d|\\-|\\.|\\/\\[\\]]+)('|\")");
//RegExp hint("(?:HINT|hint)=(?:\"|')([a-zA-Z\\s&;\\|-]+)(?:\"|')");
RegExp hint("(?:HINT|hint)=(?:\"|')([\\w|&|;|\\s|\\||\\d|\\-|\\!|\\.\\[\\]\\>]+)(?:\"|')");
RegExp color("(?:c(?:olor)? |C(?:OLOR)? )(?:fore=|FORE=)?([\\w|\\d|#]+)\\s?(?:back=|BACK=)?([\\w|\\d|#]+)?");
MudMainFrame *f = wxGetApp().GetFrame();
MudWindow *mw = m_parent;	
	if (m_mxpmode==MXP_MODE_LOCKLOCKED || m_mxpmode==MXP_MODE_LOCKED)
	{
		wxString s ="<"+t->GetTag()+">";
		mw->ParseNBuffer((char*)s.To8BitData().data(), false);
		t->Reset();
		return true;
	}
	if (t->IsEmpty())
		return false;
	if (t->GetTag().Lower().StartsWith("!en"))
	{
		this->ParseEntity("<"+t->GetTag());
		t->Reset();
		return false;
	}
	
	t->ReplaceEntitys();
	wxString ss = t->GetTag().BeforeFirst(' ').Lower();
	//wxString params = t->GetTag().AfterFirst(' ');
	vector<wxString> v_parms;
	v_parms = SplitString(" ", t->GetTag().AfterFirst(' '));
	//ss = ss.Lower();
	
	vector<class amcMXPElement>::iterator it;
	it = m_elems.begin()+elnum;
	//for (it=m_elems.begin();it!=m_elems.end();it++)
	//{
		//if (!it->GetName().CmpNoCase(ss))//Tag Found in !ELEMENTS
		//{
			//t->GetText().Replace("<BR>", "\r\n");
			if (it->HasRoomFlag())//FLAG=Room..lets ignore that
			{
				if (!t->GetText().empty())
				{
					mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
					return false;
				}
				else return false;
			}
			
			if (it->HasSetVarFlag())
			{
				if (t->GetText().empty())
					return true;
				wxString varname = it->GetVarName();
				int idx = f->GetVarIndexByLabel(varname);
				if (idx!=-1)
					f->GetVars()->at(idx).SetValue(t->GetStrippedText());
				if (!f->GetGlobalOptions()->UseUTF8())
					mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
				else mw->ParseNBuffer((char*)t->GetText().ToUTF8().data(), false);
				//mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
				//f->m_child->ParseBuffer(t->GetText().char_str());
				return false;
			}
			if (it->IsSendTag())
			{
				wxString command;
				//ale_it bit = f->m_child->GetLineStyle(f->m_child->m_curline-1)->end()-1;
				if (t->GetText().empty())
					return true;
				int ii, i; //= f->m_child->GetLineStyle(f->m_child->m_curline-1)->size();		
				int line = mw->m_curline-1;
				//wxString send = "\x1b[4m"+t->GetText()+"\x1b[0m";
				if (!f->GetGlobalOptions()->UseUTF8())
					mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
				else mw->ParseNBuffer((char*)t->GetText().ToUTF8().data(), false);
				mw->GetLineIndices(&ii, &i);
				if (line<mw->m_curline-1)
				{
					line++;
					ii=0;
				}
				ale_it ait = mw->GetLineStyle(line)->begin()+ii;
				//if (!ii)
				//	ait = f->m_child->GetLineStyle(line)->begin();
				if (ait!=mw->GetLineStyle(line)->begin() && mw->GetLineStyle(line)->size()>1)
				{
					ale_it iit = ait-1;
					if (!t->GetText().StartsWith("\x1b["))
						ait->SetFCol(iit->GetFColIndex(), iit->GetFCol());
				}
				else if (!ii)
				{
					AnsiLineElement ale;
					if (mw->GetLineStyle(line-1)->size()>2)
						ale	 = mw->GetLineStyle(line-1)->at(mw->GetLineStyle(line-1)->size()-2);
					else
						ale	 = mw->GetLineStyle(line-1)->at(0);
					ait->SetFCol(ale.GetFColIndex(), ale.GetFCol());
				}
								
				for (int c = ii; c<i;c++)
				//for(ait = f->m_child->GetLineStyle(line)->begin()+ii;ait!=f->m_child->GetLineStyle(line)->begin()+i-1;ait++)
				{
					ait = mw->GetLineStyle(line)->begin()+c;
					ait->SetMXPSend(true);
					ait->SetFontStyle(4);
					if (it->IsSendPrompt())
						ait->SetPromptSend(true);
					s_it sit;
					wxString hint = it->GetHint();
					if (!hint.Cmp(""))
						hint = t->GetText();
					//ReplaceEntities(&hint);
					hint.Replace("&text;", t->GetStrippedText());
					
					if (it->GetSendCommands()->empty())
					{
						ait->AddMXPCommand(t->GetStrippedText());
						ait->AddMXPLabel(t->GetStrippedText());
						ait->SetHint(hint);
						continue;
					}
					
					for (sit = it->GetSendCommands()->begin();sit!=it->GetSendCommands()->end();sit++)
					{
						command = *sit;
						command.Replace("&text;", t->GetStrippedText());//t->GetText());
						ReplaceEntities(&command);
						if (!v_parms.empty() && it->HasAttributes())
						{
							vector<wxString>::iterator vit;
							int i=0;
							for (vit=v_parms.begin();vit!=v_parms.end();vit++, i++)
							{
								command.Replace("&"+it->GetAttr(i)+";", *vit);
								hint.Replace("&"+it->GetAttr(i)+";", *vit);
							}
						}
						command.Replace("&quot;", "\"");
						ait->AddMXPCommand(command);
					}
					for (sit = it->GetLabels()->begin();sit!=it->GetLabels()->end();sit++)
					{
						command = *sit;
						command.Replace("&text;", t->GetStrippedText());//t->GetText());
						ReplaceEntities(&command);
						if (!v_parms.empty() && it->HasAttributes())
						{
							vector<wxString>::iterator vit;
							int i=0;
							for (vit=v_parms.begin();vit!=v_parms.end();vit++, i++)
							{
								command.Replace("&"+it->GetAttr(i)+";", *vit);
								hint.Replace("&"+it->GetAttr(i)+";", *vit);
							}
						}
						command.Replace("&quot;", "\"");
						ait->AddMXPLabel(command);
					}
					hint.Replace("|", "\n");
					ait->SetHint(hint);
				}
				return false;
			}
			if (it->HasColor()) //color tag
			{
				AnsiLineElement ale;
				ale.SetFCol(99, it->GetTag()->GetFCol());
				ale.SetBCol(99, it->GetTag()->GetBCol());
				if (mw->GetLines()->at(mw->m_curline-1).IsFull())
				{
					mw->m_curline++;
					AnsiLine line;
					mw->GetLines()->push_back(line);
				}
				mw->GetLineStyle(mw->m_curline-1)->push_back(ale);
				//f->m_child->GetLines()->at(f->m_child->m_curline-1).SetFull(false);
				//f->m_child->ParseNBuffer((char*)t->GetText().To8BitData().data());
				mw->ParseNBuffer(t->GetText().char_str());
				/*ale.SetText("");
				ale.SetFCol(7, f->m_child->GetAnsiColor(7));
				ale.SetBCol(0, f->m_child->GetAnsiColor(0));
				
				f->m_child->GetLineStyle(f->m_child->m_curline-1)->push_back(ale);*/
				t->Reset();
				return false;
			}
			//f->m_child->ParseNBuffer((char*)t->GetText().To8BitData().data());
			if (!f->GetGlobalOptions()->UseUTF8())
					mw->ParseNBuffer((char*)t->GetText().To8BitData().data(), false);
				else mw->ParseNBuffer((char*)t->GetText().ToUTF8().data(), false);
			//mw->ParseNBuffer(t->GetText().char_str(), false);
			return false;
		//}
			
	//}
return false;
}

vector<wxString> amcMXP::SplitString(wxString c, wxString split)
{
size_t pos = 0;
vector<wxString> v;
wxString::iterator sit;
int parse=0;
wxString temp;
if (split.empty())
	return v;
for (sit=split.begin();sit!=split.end();sit++)
{
	switch(parse)
	{
		case 0:
			if (*sit=='"' || *sit=='\'')
				parse = 1;
			else if (*sit==' ')
				parse = 2;
			else temp.Append(*sit); 
			break;
		case 1:
			if (*sit=='"' || *sit=='\'')
			{
				parse = 0;
				if (temp.Find('=')!=wxNOT_FOUND)
					v.push_back(temp.AfterFirst('='));
				else v.push_back(temp);
				temp.clear();
				
			}
			else temp.Append(*sit);
			break;
		case 2:
			if (!temp.empty())
			{
				if (temp.Contains('='))
					v.push_back(temp.AfterFirst('='));
				else v.push_back(temp);
			}
			temp.clear();
			if (*sit=='"' || *sit=='\'')
				parse=1;
			else
			{
				parse=0;
				temp.Append(*sit);
			}
			break;
	}
}

if (!temp.empty())
{
	if (temp.Find('=')!=wxNOT_FOUND)
		v.push_back(temp.AfterFirst('='));
	else v.push_back(temp);
}
return v;
}

bool amcMXP::ParseElementRex(wxString s, size_t *pos)
{
amcMXPElement el;
size_t f=0;
vector<wxString> find_elems;
//size_t pos = 0;
//RegExp r("(<!ELEMENT|<!EL|<!element|<!el)\\s*");
//RegExp find("(?:>'>|>\">|\" >|' >|EMPTY>|OPEN>|DELETE>)");
RegExp ent("^(<!ENTITY|<!EN|<!entity|<!en)\\s*");
bool end = true;	
	
	wxString ss = s.substr(*pos);
	wxString::iterator it;
	int x=0, cref=0;
	if (ss.GetChar(0)!='<')
		return true;
	for (it=ss.begin();it!=ss.end();it++, x++)
	{
		if (*it=='<')
			cref++;
		if (*it=='>')
		{
			cref--;
			if (!cref)
				break;
		}
	}
	*pos+=x;
	if (it==ss.end() && cref)
		return true;
	wxString ff = ss.substr(0, x+1);
	
	if (ent.Match(ff))
	{
		return ParseEntity(ff);
		
	}
	ParseElementInternals(ff);
	
return false;
}

bool amcMXP::ParseEntityRex(wxString s, size_t *pos)
{
RegExp ent("(<!ENTITY|<!EN|<!entity|<!en)\\s*");
size_t f=0;	
	
		f = s.find(">", *pos);
		if (f != string::npos)
		{
			wxString ff = s.substr(*pos, f+1-*pos);
			
			if (!ent.Match(ff))
			{
				*pos = f+1;
				return false;
			}
			*pos = f;
			//find_elems.push_back(ff);
			ParseEntity(ff);
			return false;
		}
		else return true;
return false;
}


bool amcMXP::ParseElementInternals(wxString s)
{
amcMXPElement el;
RegExp att("ATT=(\"|')([\\w|=|\\s|&|;]+)(\"|')");
RegExp flag(".*FLAG=(\"|')(.*)(\"|').*");
RegExp tag("TAG=(\"|')(.*)(\"|').*");
RegExp name("^(<!ELEMENT |^<!EL )([\\w|-]+)\\s.*");
RegExp action(" '<([^\r\n]*)>'");
//RegExp hint("(HINT|hint)=(\"|')([\\w\\s&;\\|-]+)(\"|')");
RegExp empty("EMPTY");
RegExp color("(COLOR|C) (FORE=)?([a-zA-Z0-9#]+)\\s?(BACK=)?([a-zA-Z0-9#]+)?");
MudMainFrame* f = wxGetApp().GetFrame();
vector<amcMXPElement>::iterator e_it;
	s = s.Trim(false);
	if (name.Match(s))
		el.AppendName(name.GetMatch(1));
	for (e_it = m_elems.begin();e_it!=m_elems.end();e_it++)
	{
		if (!el.GetName().Cmp(e_it->GetName()))//element already defined!! ignore this for the moment
			return false;
	}
	if (flag.Match(s, true))
		el.AppendFlag(flag.GetMatch(1));
	if (att.Match(s, true))
	{
		el.AppendAtt(att.GetMatch(1));
		el.SetAttFlag(true);
	}
	if (tag.Match(s, true))
		el.AppendTag(tag.GetMatch(1));
	if (action.Match(s))
		el.AppendAction(action.GetMatch(0));
	if (color.Match(s))
	{
		wxColour c;
		wxString m = color.GetMatch(2);
		if (m.StartsWith("#"))
			c.Set(m);
		else c = m_mxpcolor[m.Lower()];
		el.GetTag()->SetFCol(c);
		m=color.GetMatch(4);
		if (m!=wxEmptyString)
		{
			if (m.StartsWith("#"))
				c.Set(m);
			else c = m_mxpcolor[m.Lower()];
			el.GetTag()->SetBCol(c);
		}
		el.SetColor(true);
	}
	if (el.GetFlag().StartsWith("Room"))
		el.SetRoomFlag(true);
	if (el.GetFlag().Lower().StartsWith("set"))
	{
		el.SetVarFlag(true);
		amcVar v("mxp_"+el.GetFlag().AfterFirst(' '), "", "mxp_autovar");
		if (f->GetVarIndexByLabel(v.GetName())==-1)
		{
			f->GetVars()->push_back(v);
			el.SetVarName("mxp_"+el.GetFlag().AfterFirst(' '));
		}
	}
	if (el.GetFlag().Lower().StartsWith("prompt"))
		el.SetPromptFlag(true);
	if (el.GetAction().Lower().StartsWith("send"))
		el.SetSendTag(true);
	if (el.IsSendTag())
	{
		el.BuildMXPSendCommands();
		if (el.GetAction().Find("PROMPT")!=wxNOT_FOUND)
			el.SetPromptSend(true);
		//if (hint.Match(s))
		//	el.SetHint(hint.GetMatch(2));
	}
	if (el.HasAttributes())
		el.BuildAttributes();
	if (empty.Match(s))
		el.SetEmptyFlag(true);
	m_elems.push_back(el);
	//wxGetApp().GetChild()->Msg(el.GetName());
	//wxGetApp().GetChild()->Msg(el.GetAction());
return false;
}

bool amcMXP::ParseEntity(wxString s)
{
	RegExp name("(?:<!ENTITY |<!EN |<!entity |<!en )(\\w+)\\s(?:'|\")?([\\w|\\s|\\.|,|;|#|\\||\\/|\\-|'|\\[|\\]|\\(|\\)|\\d]+)(?:'|\")?(?: desc=.*)?(?: private|publish|add|remove|delete|PUBLISH|PRIVATE|DELETE)?>");
	amcMXPEntity en;
	int x=-1;
	if (!name.Match(s))
		return true;
	wxString find = name.GetMatch(0);
	x = FindEntity(find);
	if (x !=-1)
	{
		
		m_entities.at(x).SetValue(name.GetMatch(1));
		return false;
	}
	en.SetName(find);
	en.SetValue(name.GetMatch(1));
	m_entities.push_back(en);
	return false;
}

void amcMXP::ReplaceEntities(wxString* s)
{
	vector<class amcMXPEntity>::iterator it;
	for (it = m_entities.begin(); it!=m_entities.end(); it++)
	{
		s->Replace("&"+it->GetName()+";", it->GetValue());
	}
	//to do html entities replace
	ReplaceHtmlEntities(s);
	/*s->Replace("&gt;", ">");
	s->Replace("&lt;", "<");
	s->Replace("&amp;", "&");
	s->Replace("&quot;", "\"");
	s->Replace("&apos;", "'");
	s->Replace("&nbsp;", " ");
	s->Replace("&#39;", "'");*/
}

void amcMXP::ReplaceHtmlEntities(wxString* s)
{
	//to do html entities replace
	s->Replace("&gt;", ">");
	s->Replace("&lt;", "<");
	s->Replace("&amp;", "&");
	s->Replace("&quot;", "\"");
	s->Replace("&apos;", "'");
	s->Replace("&nbsp;", " ");
	for (size_t i=10;i<255;i++)
	{
		wxString en;
		en<<"&#"<<i<<";";
		s->Replace(en, wxUniChar(i));
	}
	//s->Replace("&#39;", "'");
}

int amcMXP::FindEntity(wxString f)
{
	vector<amcMXPEntity>::iterator eit;
	int i=0;
	for (eit=m_entities.begin();eit!=m_entities.end();eit++, i++)
	{
		if (!eit->GetName().Cmp(f))
			return i;
	}
	return -1;
}

int amcMXP::FindElement(wxString f)
{
	vector<amcMXPElement>::iterator eit;
	int i=0;
	f= f.BeforeFirst(' ');
	for (eit=m_elems.begin();eit!=m_elems.end();eit++, i++)
	{
		if (!eit->GetName().CmpNoCase(f))
			return i;
	}
	return -1;
}

amcMXPTag::amcMXPTag()
{
	m_tag = m_endtag = m_text = wxEmptyString;
	m_back.Set("BLACK");
	m_fore.Set("GREY");
	m_fontsize = 12;
#ifdef __WXMSW__
	m_fontname = "Monospace";
#else
	m_fontname = "Fixed";
#endif	
	m_fontattr = 0;
}

amcMXPTag::~amcMXPTag()
{
}

amcMXPTag& amcMXPTag::operator =(const amcMXPTag & at)
{
	m_tag = at.m_tag;
	m_endtag = at.m_endtag;
	m_text = at.m_text;
	m_param = at.m_param;
	m_fore = at.m_fore;
	m_back = at.m_back;
	m_fontattr = at.m_fontattr;
	m_fontsize = at.m_fontsize;
	m_fontname = at.m_fontname;
	return *this;
}

void amcMXPTag::ReplaceEntitys()
{
	m_text.Replace("&lt;", "<");
	m_text.Replace("&gt;", ">");
	m_text.Replace("&amp;", "&");
	m_text.Replace("&quot;", "\"");
	m_text.Replace("&nsbp;", " ");
	m_text.Replace("&apos;", "'");
}

wxString amcMXPTag::GetStrippedText()
{
	wxString::const_iterator it;
	wxString result;
	int parse = 0;
	for (it = m_text.begin();it!=m_text.end();it++)
	{
		switch(parse)
		{
		case 0:
			if (*it=='\x1b')
				parse=1;
			else result.Append(*it);
			break;
		case 1:
			if (*it=='m')
				parse=0;
			break;
		}
	}
	result.Replace("\r", "");
	result.Replace("\n", " ");
	return result;
}

bool amcMXPTag::IsEmpty()
{
	return (m_tag.empty() && m_endtag.empty() && m_text.empty());
}

bool amcMXPTag::IsMXPTag()
{
	//look if this is literally sent by the mud
	return (!m_tag.CmpNoCase("user") || !m_tag.CmpNoCase("password") || !m_tag.CmpNoCase("version") ||
		m_tag.Lower().StartsWith("support") || m_tag.Lower().StartsWith("expire") || m_tag.Lower().StartsWith("color ") ||
		m_tag.Lower().StartsWith("c ") || m_tag.Lower().StartsWith("send") || m_tag.Lower().StartsWith("a ") ||
		m_tag.Lower().IsSameAs('a'));
}

bool amcMXPTag::IsOpenTag()
{
	//look if this is literally sent by the mud
	return (!m_tag.Lower().CmpNoCase("bold") ||	!m_tag.Lower().CmpNoCase("b") || !m_tag.Lower().CmpNoCase("underline") ||
		!m_tag.Lower().CmpNoCase("u") || !m_tag.Lower().CmpNoCase("strikeout") ||
		!m_tag.Lower().CmpNoCase("s") || !m_tag.Lower().CmpNoCase("italic") ||	!m_tag.Lower().CmpNoCase("i"));
}

void amcMXPTag::Reset()
{
	m_tag = m_endtag = m_text = wxEmptyString;
	m_back.Set("BLACK");
	m_fore.Set("GREY");
	m_fontsize = 12;
	#ifdef __WXMSW__
		m_fontname = "Monospace";
	#else
		m_fontname = "Fixed";
	#endif	
	m_fontattr = 0;
	m_param.clear();
}

amcMXPElement::amcMXPElement()
{
	m_name = wxEmptyString;
	m_action = wxEmptyString;
	m_properties = wxEmptyString;
	m_tag = m_att = m_flag = m_hint = wxEmptyString;
	m_empty = m_open = m_delete = false;
	m_isroomflag = m_ispromptflag = m_issetvar = m_boatt = m_sendprompt = m_bocolor = false;
	m_sendtag = false;
}

amcMXPElement::~amcMXPElement()
{
	//delete m_tag;
	//m_tag = 0;
}

void amcMXPElement::BuildMXPSendCommands()
{
//split a send string;
size_t p, pos = 0;
wxString build;
RegExp r("send (?:hint=.+ |prompt )?(?:hint=.+ |prompt )?(?:href=)?('|\")([\\?+|\\w+|&+|;+|\\s+|\\+||#+|\\d+|\\-+|\\.+|\\!+|\\(+|\\)+]+)('|\")?(?: PROMPT|prompt)?");
RegExp r2("send (?:hint=.+ |prompt )?(?:hint=.+ |prompt )?(?:href=)?([\\?+|\\w+|&+|;+|\\+||#+|\\d+|\\-+|\\.+|\\!+|\\(+|\\)+]+)\\s*");

//RegExp hint("(?:HINT|hint)=(?:\"|')([a-zA-Z\\s&;\\|-]+)(?:\"|')");
RegExp hint("(?:HINT|hint)=(?:\"|')([\\w|&|;|\\s|\\||\\d|\\-|\\!|\\.]+)(?:\"|')");
RegExp hint2("(?:HINT|hint)=([\\w|&|;|\\||\\d|\\-|\\!|\\.]+)\\s*");
	if (!r.Match(m_action.Lower()))
	{
		if (!r2.Match(m_action.Lower()))
		{
			return;
		}
		else
		{
			build = r2.GetMatch(0);
			if (build.StartsWith("EXPIRE") || build.StartsWith("expire"))
			{
				return;

			}
		}
	}
	else
		build = r.GetMatch(1);
	do
	{
		p = build.find("|", pos);
		if (p != string::npos)
		{
			wxString ff = build.substr(pos, p-pos);
			pos = p+1;
			m_sendcommands.push_back(ff);
		}
	
	} while (p != string::npos);
	if (p==string::npos && pos< build.length())// && m_sendcommands.empty())
	{
		m_sendcommands.push_back(build.substr(pos));
	}
	if (!hint.Match(m_action))
	{
		if (!hint2.Match(m_action))
		{
			m_labels = m_sendcommands;
			m_hint = m_labels.at(0);
			return;
		}
		else
			build = hint2.GetMatch(0);
	}
	else
		build = hint.GetMatch(0);
	pos = 0;
	do
	{
		p = build.find("|", pos);
		if (p != string::npos)
		{
			wxString ff = build.substr(pos, p-pos);
			pos = p+1;
			m_labels.push_back(ff);
		}
	
	} while (p != string::npos);
	if (p==string::npos && pos< build.length())// && m_sendcommands.empty())
	{
		m_labels.push_back(build.substr(pos));
	}
	m_hint = m_labels.at(0);
	if (m_labels.size()<=1)
	{
		
		m_labels = m_sendcommands;
	}
	if (m_labels.size()>m_sendcommands.size())
		m_labels.erase(m_labels.begin());
	
}

void amcMXPElement::BuildAttributes()
{
//split a send string;
size_t p, p2, pos = 0;
//RegExp r("SEND HREF=('|\")([\\w|&|;|\\s|\\|]+)('|\")");

	do
	{
		p = m_att.find(" ", pos);
		if (p != string::npos)
		{
			
			wxString ff = m_att.substr(pos, p-pos);
			p2 = ff.find('=');
			if (p2!=string::npos)
				ff = ff.substr(pos, p2-pos);
			//ff = ff.AfterFirst(' ');
			pos = p+1;
			m_attributes.push_back(ff);
		}
	
	} while (p != string::npos);
	if (p==string::npos && pos< m_att.length())// && m_attributes.empty())
	{
		wxString ff = m_att.substr(pos);
		p2 = ff.find('=');
		if (p2!=string::npos)
			ff = ff.substr(0, p2);
		m_attributes.push_back(ff);
	}
}

void amcMXPElement::Clear()
{
	m_name.clear();
	m_action.clear();
	m_properties.clear();
}

amcMXPEntity::amcMXPEntity()
{
	m_publish = false;
	m_delete = false;
	m_add = false;
	m_remove = false;
	m_name = m_value = wxEmptyString;
}

amcMXPEntity::~amcMXPEntity()
{
}

