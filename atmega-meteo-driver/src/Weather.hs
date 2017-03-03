module Weather where

import Data.ByteString.Lazy (ByteString)
import Network.HTTP.Simple (httpLBS, parseRequest, getResponseBody)
import Text.XML.Light

type Weather = (Double, Double)

fetchWeather :: IO ByteString
fetchWeather = do
  request <- parseRequest "http://meteo.ftj.agh.edu.pl/meteo/meteo.xml"
  getResponseBody <$> httpLBS request

getWeather :: IO (Maybe Weather)
getWeather = parseWeather <$> fetchWeather

parseWeather :: ByteString -> Maybe Weather
parseWeather xml = do
  root <- parseXMLDoc xml >>= findChild (QName "dane_aktualne" Nothing Nothing)
  temp <- read . head . words . strContent <$> findChild (QName "ta" Nothing Nothing) root
  humid <- read . head . words . strContent <$> findChild (QName "ua" Nothing Nothing) root
  return $ (temp, humid)
