//#pragma once
//
//#include "app.h"
//
//#include <ft2build.h>
//#include FT_FREETYPE_H
//
//#include <algorithm> // For std::max
//#include <glm/glm.hpp>
//
//void dzg::loadFont(int fontSize)
//{
//    static std::string FONTS_FOLDER = "../resources/fonts/";
//    std::string fontName = m_scene->TextureAtlas->Name;
//
//    FT_Library fontLibrary;
//    FT_Init_FreeType(&fontLibrary);
//
//    FT_Face fontFace;
//    FT_New_Face(fontLibrary, (FONTS_FOLDER + fontName).c_str(), 0, &fontFace);
//    FT_Set_Pixel_Sizes(fontFace, 0, fontSize);
//
//    int padding = 2;
//    int row = 0;
//    int col = padding;
//
//    const int textureWidth = 512;
//    char textureBuffer[textureWidth * textureWidth];
//    for (FT_ULong glyphIdx = 32; glyphIdx < 127; ++glyphIdx)
//    {
//        FT_UInt glyphIndex = FT_Get_Char_Index(fontFace, glyphIdx);
//        FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_DEFAULT);
//        FT_Error error = FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL);
//
//        if (col + fontFace->glyph->bitmap.width + padding >= 512)
//        {
//            col = padding;
//            row += fontSize;
//        }
//
//        // Font Height
//        //TODO store this somewhere as well
//        this->m_scene->fontHeight =
//            std::max((fontFace->size->metrics.ascender - fontFace->size->metrics.descender) >> 6, this->m_scene->fontHeight);
//
//        for (unsigned int y = 0; y < fontFace->glyph->bitmap.rows; ++y)
//        {
//            for (unsigned int x = 0; x < fontFace->glyph->bitmap.width; ++x)
//            {
//                textureBuffer[(row + y) * textureWidth + col + x] =
//                    fontFace->glyph->bitmap.buffer[y * fontFace->glyph->bitmap.width + x];
//            }
//        }
//
//        Glyph* glyph = &this->m_scene->glyphs[glyphIdx];
//        glyph->textureCoords = { col, row };
//        glyph->size =
//        {
//          (int)fontFace->glyph->bitmap.width,
//          (int)fontFace->glyph->bitmap.rows
//        };
//        glyph->advance =
//        {
//          (float)(fontFace->glyph->advance.x >> 6),
//          (float)(fontFace->glyph->advance.y >> 6)
//        };
//        glyph->offset =
//        {
//          (float)fontFace->glyph->bitmap_left,
//          (float)fontFace->glyph->bitmap_top,
//        };
//
//        col += fontFace->glyph->bitmap.width + padding;
//    }
//
//    FT_Done_Face(fontFace);
//    FT_Done_FreeType(fontLibrary);
//
//    this->createFontAtlas((char*)textureBuffer);
//}